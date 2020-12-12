/*
 * kernel.c - Source file for kernel, main operation source code.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 ***********************************************************************
 */

#include <stdbool.h>

#include "kernel.h"
#include "isr.h"
#include "vga.h"
#include "helper.h"
#include "io.h"
#include "shell.h"
#include "keyboard.h"
#include "timer.h"
#include "system.h"

#define isascii(c) ((unsigned)(c) <= 0x7F)
#define MAXBUF 100

bool kbd_istyping;
bool login_active;

/* Sleep for a specific number of ticks.
 */
static void delay(unsigned int ticks)
{
	unsigned int eticks = get_timer_ticks()+ticks;
	while(get_timer_ticks() < eticks);
}
/* Sleep for a specific number of seconds.
 */
static void sleep(unsigned int seconds)
{
	unsigned int eseconds = get_timer_seconds()+seconds;
	while(get_timer_seconds() < eseconds);
}
/* Get key from keyboard.
 */
static int getch(void)
{
	KEYCODE key = KEY_UNKNOWN;
	
	while(key == KEY_UNKNOWN)
		key = kbd_get_last_key();
	kbd_discard_last_key();
	return key;
}
/* Get command from user and put to buffer.
 */
static void get_command(char *buf, int size)
{
		KEYCODE key;
		bool buf_char;
		int i = 0;

		while(i < size) {
			buf_char = true;
			key = getch();

			if(key == KEY_RETURN) {
				kputc('\n');
				kbd_istyping = false;
				break;
			}

			if(key == KEY_BACKSPACE) {
				if(i > 0) {
					buf[i-1] = 0;
					kbd_istyping = true;
					i--;
				} else {
					kbd_istyping = false;
				}
			}

			if(buf_char) {
				char c = kbd_key_to_ascii(key);
				buf[i++] = c;
				kbd_istyping = true;
				kputc(c);
			}
			delay(3);
		}
		buf[i] = 0;
}
/* Entry point for kernel.
 */
static void kernel_main(void)
{
	const unsigned char snd[] = {0x3f, 0x4F, 0x5F, 0x3F, 0x7F};
	const int tsnd = sizeof(snd)/sizeof(snd[0]);
	char key_buffer[MAXBUF];

	// Initialize the terminal and install ISRs and IRQs.
	term_init(BLUE, YELLOW);
	isr_install();
	irq_install();

	// Display loading message and play music.
	kprintf("Loading system! Please wait");
	for(int i = 0; i < tsnd; i++) {
		sound(snd[i]);
		delay(5);
		sound(0);
		sleep(1);
	}
	sound(0);
	clear_screen();
	
	// Display welcome message to user and prompt.
	kprintf(WELCOME_MESSAGE);
	for(;;) {
#if 1		// This works!
		KEYCODE key;
		bool buf_char;
		int i = 0;

		while(i < MAXBUF) {
			buf_char = true;
			key = getch();

			if(key == KEY_RETURN) {
				kputc('\n');
				kbd_istyping = false;
				break;
			}

			if(key == KEY_BACKSPACE) {
				if(i > 0) {
					key_buffer[i-1] = 0;
					kbd_istyping = true;
					i--;
				} else {
					kbd_istyping = false;
				}
			}

			if(buf_char) {
				char c = kbd_key_to_ascii(key);
				key_buffer[i++] = c;
				kbd_istyping = true;
				kputc(c);
			}
			delay(3);
		}
		key_buffer[i] = 0;

		// Handle login
		if(login_active) {
			if(!strcmp("root071", key_buffer)) {
				login_active = false;
				kprintf("Login successful!\n");
				sleep(2);
				kprintf("Please type 'help' for a list of commands.\n> ");
			} else {
				login_active = true;
				kprintf("Login failed.\nLOGIN? ");
			}
		} else {
			process_command(key_buffer);
			if(!login_active) kprintf("> ");
		}
#else		// This doesn't! Why?
		if(login_active) {
			get_command(key_buffer, MAXBUF);
			if(!strcmp("root071", key_buffer)) {
				login_active = false;
				kprintf("Login successful!\n");
				sleep(2);
				kprintf("Please type 'help' for a list of commands.\n> ");
			} else {
				login_active = true;
				kprintf("Login failed!\nLOGIN? ");
			}
		} else {
			get_command(key_buffer, MAXBUF);
			process_command(key_buffer);
			if(!login_active) kprintf("> ");
		}
#endif
	}
}
/* Start of operating system.
 */
void _start(void)
{
	// Initialize variables and start main routine
	kbd_istyping = false;
	login_active = true;
	kernel_main();
}
