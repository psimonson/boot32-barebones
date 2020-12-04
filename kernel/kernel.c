/*
 * kernel.c - Source file for kernel, main operation source code.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 ***********************************************************************
 */

#include <stdbool.h>

#include "isr.h"
#include "vga.h"
#include "helper.h"
#include "io.h"
#include "shell.h"
#include "keyboard.h"

char key_buffer[256]; // Used to store keyboard input.
bool kbd_istyping;

extern int get_command(char *buf, int size);

/* Entry point for kernel.
 */
void kernel_main(void)
{
	// Display welcome message to user and prompt.
	kprintf("Welcome to my bare bones example 32 bit operating system.\n");
	kprintf("\n  I have designed this because I would like to teach beginners\n");
	kprintf("the proper way of doing things. As far as a beginning operating\n");
	kprintf("system goes. Please feel free to clone and use it. If you are\n");
	kprintf("are wondering about what license. It has an MIT license so\n");
	kprintf("basically don't say you wrote it and you'll be fine. Other than\n");
	kprintf("that, you can use it for whatever you want. Also this software\n");
	kprintf("comes WITHOUT ANY WARRANTY of any kind. I will not be held\n");
	kprintf("accountable for any damage this software may cause. Please use\n");
	kprintf("it at your own risk.\n\n");
	kprintf("Cheers,\nPhilip R. Simonson (aka 5n4k3)\n\n");
	kprintf("Welcome to a bare bones kernel! This is a temporary shell.\n");
	kprintf("Please type 'help' to see what you can do.\n\n");
	while(get_command(key_buffer, sizeof(key_buffer)) > 0)
		process_command(key_buffer);
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

	kprintf("> ");
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
	}
	buf[i] = 0;
	return i;
}
/* Start of operating system.
 */
 void _start(void)
 {
 	// Initialize the terminal and install ISRs and IRQs.
	term_init(BLUE, YELLOW);
	isr_install();
	irq_install();
	kbd_istyping = false;
 	kernel_main();
 }
