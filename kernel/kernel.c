/*
 * kernel.c - Source file for kernel, main operation source code.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 ***********************************************************************
 */

#include <stdbool.h>

#include "hal.h"
#include "kernel.h"
#include "helper.h"
#include "isr.h"
#include "vga.h"
#include "io.h"
#include "shell.h"
#include "keyboard.h"
#include "system.h"

#define isascii(c) ((unsigned)(c) <= 0x7F)
#define MAXBUF 100

bool kbd_istyping;
bool login_active;
bool regs_update;

/* Get key from keyboard.
 */
int getch(void)
{
	KEYCODE key = KEY_UNKNOWN;
	
	while(key == KEY_UNKNOWN)
		key = kbd_get_last_key();
	kbd_discard_last_key();
	return key;
}
/* Get command from user and put to buffer.
 */
void get_command(char *buf, int size)
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
					buf[i] = '\0';
					kputc('\b');
					--i;
				}
				continue;
			}

			// Update if keyboard is typing or not.
			kbd_istyping = buf_char;

			if(buf_char) {
				if(isascii(key)) {
					char c = kbd_key_to_ascii(key);
					buf[i++] = c;
					kputc(c);
				}
			}

			delay(5);
		}
		buf[i] = '\0';
}
/* Entry point for kernel.
 */
void kernel_main(void)
{
	const unsigned short snd[] = {500, 1000, 3000, 1500, 800};
	const int tsnd = sizeof(snd)/sizeof(snd[0]);
	char key_buffer[MAXBUF];

	// Initialize terminal
	term_init(BLUE, YELLOW);
	hal_init();

	// Initialize the variables.
	kbd_istyping = false;
	login_active = true;

	// Display loading message and play music.
	kprintf("Loading system! Please wait");
	for(int i = 0; i < tsnd; i++) {
		kputc('.');
		sound(snd[i]);
		delay(5);
		sound(0);
		delay(10);
	}
	sound(0);
	clear_screen();
	
	// Display welcome message to user and prompt.
	kprintf(WELCOME_MESSAGE);
	for(;;) {
		get_command(key_buffer, sizeof(key_buffer));

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
	}
}
