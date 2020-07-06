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

static char key_buffer[256]; // Save the keys pressed

char kbdus_table[128] = {
	0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u',
	'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f',
	'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z',
	'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0,
	' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-',
	0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* Handle keyboard input from user.
 */
static void keyboard_callback(registers_t *regs)
{
	static unsigned char multibyte = 0;
	char scancode = inb(0x60);

	multibyte = scancode;
	if(multibyte >= 0xe0) {
		if(scancode >= 0x80) {
			/* TODO: Handle two byte release. */
		} else {
			/* TODO: Handle two byte press. */
		}
		multibyte = 0;
	} else if(multibyte == 0xe1) {
		switch(scancode) {
			case 0x1d:
			case 0x45:
			case 0x9d:
			case 0xe1:
				/* TODO: Verify correct order */
			break;
			case 0xc5:
				/* TODO: Handle pause key */
				multibyte = 0;
			break;
			default:
				/* Shouldn't happen, perhaps warn user. */
				multibyte = 0;
			break;
		}
	} else {
		if(scancode >= 0x80) {
			/* TODO: Handle one byte release. */
		} else {
			if(scancode == '\b') { // Backspace
				backspace(key_buffer);
				print_bkspc();
			} else if(scancode == '\n') { // Enter/Return
				user_input(key_buffer);
				key_buffer[0] = '\0';
			} else {
				char letter = kbdus_table[multibyte];
				char str[2] = {letter, '\0'};
				append(key_buffer, letter);
				print(str);
			}
		}
	}
	(void)regs;
}
/* Initialize the keyboard.
 */
void install_keyboard(void)
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}
