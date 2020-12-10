/*
 * keyboard.c - Source file for simple keyboard input.
 *
 * Author: Philip R. Simonson
 * Date  : 07/04/2020
 *
 ******************************************************************
 */

#include "keyboard.h"
#include "kernel.h"
#include "helper.h"
#include "io.h"
#include "ports.h"
#include "isr.h"
#include "util.h"

#define APPEND_KEYS(K, ...) K, ##__VA_ARGS__
#define BUILD_KBD_ERR(S, X) S = X

#define isascii(c) ((unsigned)(c) <= 0x7F)

/* Scan error codes */
enum KBD_ERROR {
	BUILD_KBD_ERR(KBD_ERR_BUF_OVERRUN, 0),
	BUILD_KBD_ERR(KBD_ERR_ID_RET, 0x83AB),
	BUILD_KBD_ERR(KBD_ERR_BAT, 0xAA),
	BUILD_KBD_ERR(KBD_ERR_ECHO_RET, 0xEE),
	BUILD_KBD_ERR(KBD_ERR_ACK, 0xFA),
	BUILD_KBD_ERR(KBD_ERR_BAT_FAILED, 0xFC),
	BUILD_KBD_ERR(KBD_ERR_DIAG_FAILED, 0xFD),
	BUILD_KBD_ERR(KBD_ERR_RESEND_CMD, 0xFE),
	BUILD_KBD_ERR(KBD_ERR_KEY, 0xFF)
};

extern char key_buffer[];
extern bool kbd_istyping;
int _scancode;

static bool _kbd_bat_res;
static bool _kbd_diag_res;
static bool _kbd_resend_res;

static bool _numlock;
static bool _scrolllock;
static bool _capslock;
static bool _ctrl;
static bool _shift;
static bool _alt;

static int _kbd_std_table[] = {
	APPEND_KEYS(KEY_UNKNOWN, KEY_ESCAPE, KEY_1, KEY_2, KEY_3, KEY_4),
	APPEND_KEYS(KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS),
	APPEND_KEYS(KEY_EQUAL, KEY_BACKSPACE, KEY_TAB, KEY_Q, KEY_W, KEY_E),
	APPEND_KEYS(KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P),
	APPEND_KEYS(KEY_LEFTBRACKET, KEY_RIGHTBRACKET, KEY_RETURN, KEY_LCTRL),
	APPEND_KEYS(KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L),
	APPEND_KEYS(KEY_SEMICOLON, KEY_QUOTE, KEY_GRAVE, KEY_LSHIFT, KEY_BACKSLASH),
	APPEND_KEYS(KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA),
	APPEND_KEYS(KEY_DOT, KEY_SLASH, KEY_RSHIFT, KEY_KP_ASTERISK, KEY_RALT),
	APPEND_KEYS(KEY_SPACE, KEY_CAPSLOCK, KEY_F1, KEY_F1, KEY_F2, KEY_F3, KEY_F4),
	APPEND_KEYS(KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_KP_NUMLOCK),
	APPEND_KEYS(KEY_SCROLLLOCK, KEY_HOME, KEY_KP_8, KEY_PAGEUP, KEY_KP_2),
	APPEND_KEYS(KEY_KP_3, KEY_KP_0, KEY_KP_DECIMAL, KEY_UNKNOWN, KEY_UNKNOWN),
	APPEND_KEYS(KEY_UNKNOWN, KEY_F11, KEY_F12)
};

/* Invalid scan code. Used to indicate the last scan code is not to be reused. */
const int INVALID_SCANCODE = 0;

/* Return scroll lock on/off.
 */
char kbd_get_scrolllock(void)
{
	return _scrolllock;
}
/* Return num lock on/off.
 */
char kbd_get_numlock(void)
{
	return _numlock;
}
/* Return caps lock on/off.
 */
char kbd_get_capslock(void)
{
	return _capslock;
}
/* Read Status from keyboard controller.
 */
static char kbd_ctrl_read_status(void)
{
	return inb(0x64);
}
/* Send command byte to keyboard controller.
 */
void kbd_ctrl_send_cmd(unsigned char cmd)
{
	while(1)
		if((kbd_ctrl_read_status() & 2) == 0)
			break;
	outb(0x64, cmd);
}
/* Read keyboard encoder buffer.
 */
static char kbd_enc_read_buf(void)
{
	return inb(0x60);
}
/* Send command byte to keyboard encoder.
 */
static void kbd_enc_send_cmd(unsigned char cmd)
{
	while(1)
		if((kbd_ctrl_read_status() & 2) == 0)
			break;
	outb(0x60, cmd);
}
/* Set LEDs on keyboard for Special keys.
 */
static void kbd_set_leds(bool num, bool caps, bool scroll)
{
	unsigned char data = 0;
	
	data = (scroll) ? (data | 1) : (data & 1);
	data = (num) ? (data | 2) : (data & 2);
	data = (caps) ? (data | 4) : (data & 4);
	
	kbd_enc_send_cmd(0xED);
	kbd_enc_send_cmd(data);
}
/* Handle keyboard input from user.
 */
static void keyboard_callback(registers_t *regs)
{
	static char _extended = false;
	int code = 0;
	
	if(kbd_ctrl_read_status() & 1) {
		code = kbd_enc_read_buf();
		
		if(code == 0xE0 || code == 0xE1)
			_extended = true;
		else {
			_extended = false;
			
			if(code & 0x80) {
				/* Convert the break to into it make code equivelant. */
				code -= 80;
				
				int key = _kbd_std_table[code];
				switch(key) {
					case KEY_LCTRL:
					case KEY_RCTRL:
						_ctrl = false;
					break;
					case KEY_LSHIFT:
					case KEY_RSHIFT:
						_shift = false;
					break;
					case KEY_LALT:
					case KEY_RALT:
						_alt = false;
					break;
					default:
					break;
				}
			} else {
				/* This is a make code set the scan code. */
				_scancode = code;
				
				int key = _kbd_std_table[code];
				switch(key) {
					case KEY_LCTRL:
					case KEY_RCTRL:
						_ctrl = true;
					break;
					case KEY_LSHIFT:
					case KEY_RSHIFT:
						_shift = true;
					break;
					case KEY_LALT:
					case KEY_RALT:
						_alt = true;
					break;
					case KEY_CAPSLOCK:
						_capslock = (_capslock) ? false : true;
						kbd_set_leds(_numlock, _capslock, _scrolllock);
					break;
					case KEY_KP_NUMLOCK:
						_numlock = (_numlock) ? false : true;
						kbd_set_leds(_numlock, _capslock, _scrolllock);
					break;
					case KEY_SCROLLLOCK:
						_scrolllock = (_scrolllock) ? false : true;
						kbd_set_leds(_numlock, _capslock, _scrolllock);
					break;
					case KEY_BACKSPACE:
/*						backspace(key_buffer);
						kputc('\b');
						kbd_istyping = true;
*/					break;
					case KEY_RETURN:
/*						kputc('\n');
						kbd_istyping = false;
						key_buffer[0] = 0;
*/					break;
					default: {
/*						char str[2] = {key, '\0'};
						kbd_istyping = true;
						append(key_buffer, key);
						kputs(str);
*/						break;
					}
				}
			}
		
			/* Watch for errors. */
			switch(code) {
				case KBD_ERR_BAT_FAILED:
					_kbd_bat_res = false;
				break;
				case KBD_ERR_DIAG_FAILED:
					_kbd_diag_res = false;
				break;
				case KBD_ERR_RESEND_CMD:
					_kbd_resend_res = true;
				break;
				default:
				break;
			}
		}
	}
	(void)regs;
}
/* Do a self test on the keyboard.
 */
static char kbd_self_test(void)
{
	return true;
}
/* Return last scan code of pressed key.
 */
u8_t kbd_get_last_scan(void)
{
	return _scancode;
}
/* Return last key that was pressed.
 */
KEYCODE kbd_get_last_key(void)
{
	return (_scancode != INVALID_SCANCODE) ? ((KEYCODE)_kbd_std_table[_scancode]) : KEY_UNKNOWN;
}
/* Discard last key that was received.
 */
void kbd_discard_last_key(void)
{
	_scancode = INVALID_SCANCODE;
}
/* Convert keycode to ascii value.
 */
char kbd_key_to_ascii(KEYCODE code)
{
	u8_t key = code;
	
	if(isascii(key)) {
		if(_shift || _capslock) {
			if(key >= 'a' && key <= 'z')
				key -= 32;
		}
		
		if(_shift && !_capslock) {
			if(key >= '0' && key <= '9') {
				switch(key) {
					case '0':
						key = KEY_RIGHTPARENTHESIS;
					break;
					case '1':
						key = KEY_EXCLAMATION;
					break;
					case '2':
						key = KEY_AT;
					break;
					case '3':
						key = KEY_HASH;
					break;
					case '4':
						key = KEY_DOLLAR;
					break;
					case '5':
						key = KEY_PERCENT;
					break;
					case '6':
						key = KEY_CARRET;
					break;
					case '7':
						key = KEY_AMPERSAND;
					break;
					case '8':
						key = KEY_ASTERISK;
					break;
					case '9':
						key = KEY_LEFTPARENTHESIS;
					break;
					default:
						// Do nothing here
					break;
				}
			} else {
				switch(key) {
					case KEY_COMMA:
						key = KEY_GREATER;
					break;
					case KEY_DOT:
						key = KEY_LESS;
					break;
					case KEY_SLASH:
						key = KEY_QUESTION;
					break;
					case KEY_SEMICOLON:
						key = KEY_COLON;
					break;
					case KEY_QUOTE:
						key = KEY_QUOTEDOUBLE;
					break;
					case KEY_LEFTBRACKET:
						key = KEY_LEFTCURL;
					break;
					case KEY_RIGHTBRACKET:
						key = KEY_RIGHTCURL;
					break;
					case KEY_GRAVE:
						key = KEY_TILDE;
					break;
					case KEY_MINUS:
						key = KEY_UNDERSCORE;
					break;
					case KEY_EQUAL:
						key = KEY_PLUS;
					break;
					case KEY_BACKSLASH:
						key = KEY_BAR;
					break;
					default:
						// Do nothing here
					break;
				}
			}
		}
		
		return key;
	}
	
	return 0;
}
/* Initialize the keyboard.
 */
void install_kbd(void)
{
	register_interrupt_handler(IRQ1, keyboard_callback);
	
	_kbd_bat_res = kbd_self_test();
	_kbd_diag_res = _kbd_resend_res = false;
	
	kbd_istyping = false;
	_numlock = true;
	_scrolllock = _capslock = false;
	_shift = _ctrl = _alt = false;
	kbd_set_leds(_numlock, _capslock, _scrolllock);
}
