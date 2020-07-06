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

static char key_buffer[256];

#define SC_MAX 57

const char *sc_name[] = {
	"ERROR", "Esc", "1", "2", "3", "4", "5", "6", "7", "8",
	"9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
	"R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter",
	"Lctrl", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";",
	"'", "`", "LShift", "\\", "Z", "X", "C" "V", "B", "N", "M",
	",", ".", "/", "RShift", "Keypad *", "LAlt", "Spacebar"
};

const char sc_ascii[] = {
	'?', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
	'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D',
	'F', 'G', 'H', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z',
	'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '?', '?',
	'?', ' '
};

/* Handle keyboard input from user.
 */
static void keyboard_callback(registers_t *regs)
{
	u8_t scancode = inb(0x60);

	if(scancode > SC_MAX) return;
	if(scancode == 0x0B) { // Backspace
		backspace(key_buffer);
		print_bkspc();
	} else if(scancode == 0x0A) { // Enter/Return
		print("\n");
		user_input(key_buffer);
		key_buffer[0] = '\0';
	} else {
		char letter = sc_ascii[(int)scancode];
		char str[2] = {letter, '\0'};
		append(key_buffer, letter);
		print(str);
	}
	(void)regs;
}
/* Initialize the keyboard.
 */
void install_keyboard(void)
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}