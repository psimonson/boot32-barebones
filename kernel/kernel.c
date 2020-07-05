/*
 * kernel.c - Source file for kernel, main operation source code.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 ***********************************************************************
 */

#include "isr.h"
#include "vga.h"
#include "io.h"
#include "helper.h"

/* Entry point for kernel.
 */
void kernel_main(void)
{
	// Initialize the terminal and install ISRs and IRQs.
	term_init(BLUE, YELLOW);
	isr_install();
	irq_install();

	// Display welcome message to user and prompt.
	print("Welcome to my bare bones example 32 bit operating system.\n");
	print("\n  I have designed this because I would like to teach beginners\n");
	print("the proper way of doing things. As far as a beginning operating\n");
	print("system goes. Please feel free to clone and use it. If you are\n");
	print("are worried about a LICENSE don't be. I will NOT put a LICENSE\n");
	print("on this project. Also this software comes WITHOUT ANY WARRANTY\n");
	print("of any kind. I will not be held accountable for any damage this\n");
	print("software may cause. Please use at your own risk.\n");
	print("\n\nCheers,\nPhilip R. Simonson (aka 5n4k3)\n\n");
	print("Welcome to a bare bones kernel! This is a temporary shell.\n");
	print("Please type 'help' to see what you can do.\n\n> ");
}
/* Kernel process user input.
 */
void user_input(char *input)
{
	if(!strcmp(input, "EXIT")) {
		print("Halting CPU...\n");
		__asm__ __volatile("hlt");
	} else {
		print("Invalid command entered. Try 'help'\nto see what you can do.\n");
		print("> ");
	}
}
