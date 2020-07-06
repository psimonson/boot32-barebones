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

static char key_buffer[256];

const char ascii_table[128] = {
	'\0', '`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
	'-', '=', '\0', '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
	'o', 'p', '[', ']', '\\', '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j',
	'k', 'l', ';', '\'', '\0', '\0', 'z', 'x', 'c', 'v', 'b', 'n',
	'm', ',', '.', '/', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
	'7', '4', '1', '/', '8', '5', '2', '0', '*', '9', '6', '3',
	'.', '-', '+', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'
};

/* Handle keyboard input from user.
 */
static void keyboard_callback(registers_t *regs)
{
	int scancode = inb(0x60);

	if(scancode > 128) return;
	if(scancode == 0x0B) { // Backspace
		backspace(key_buffer);
		print_bkspc();
	} else if(scancode == 0x0A) { // Enter/Return
		print("\n");
		user_input(key_buffer);
		key_buffer[0] = '\0';
	} else {
		char letter = ascii_table[scancode];
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
