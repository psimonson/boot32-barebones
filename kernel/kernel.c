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

char key_buffer[256]; // Used to store keyboard input.
bool kbd_istyping;
bool login_active;

extern int get_command(char *buf, int size);

/* Sleep for a specific number of ticks.
 */
void sleep(unsigned int ticks)
{
	unsigned int eticks = get_timer_ticks()+ticks;
	while(get_timer_ticks() < eticks);
}
/* Entry point for kernel.
 */
void kernel_main(void)
{
	// Initialize the terminal and install ISRs and IRQs.
	term_init(BLUE, YELLOW);
	isr_install();
	irq_install();
	
	// Display welcome message to user and prompt.
	kprintf(WELCOME_MESSAGE "? ");
	for(;;) {
		if(login_active) {
			if(get_command(key_buffer, sizeof(key_buffer)) > 0)
				if(!strcmp("root071", key_buffer)) {
					login_active = false;
					kprintf("Login successful!\nPlease type 'help' "
						"for a list of commands.\n\n> ");
				} else {
					login_active = true;
					kprintf("Login failed!\nLOGIN? ");
				}
		} else {
			kprintf("> ");
			if(get_command(key_buffer, sizeof(key_buffer)) > 0)
				process_command(key_buffer);
		}
	}
}
/* Get key from keyboard.
 */
KEYCODE getch(void)
{
	KEYCODE key = KEY_UNKNOWN;
	
	while(key == KEY_UNKNOWN)
		key = kbd_get_last_key();
	kbd_discard_last_key();
	return key;
}
/* Get next command for shell.
 */
int get_command(char *buf, int size)
{
	KEYCODE key = KEY_UNKNOWN;
	bool buf_char = false;
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
			buf_char = false;
			
			if(i > 0) {
				backspace(key_buffer);
				kputc('\b');
				kbd_istyping = true;
				--i;
			} else {
				kbd_istyping = false;
			}
		}
		
		if(buf_char) {
			char c = kbd_key_to_ascii(key);
			if(c != 0) {
				kputc(c);
				buf[i++] = c;
				kbd_istyping = true;
			}
		}
		sleep(10);
	}
	buf[i] = 0;
	return i;
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
