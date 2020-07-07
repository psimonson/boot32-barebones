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
#include "shell.h"

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
	print("are wondering about what license. It has an MIT license so\n");
	print("basically don't say you wrote it and you'll be fine. Other than\n");
	print("that, you can use it for whatever you want. Also this software\n");
	print("comes WITHOUT ANY WARRANTY of any kind. I will not be held\n");
	print("accountable for any damage this software may cause. Please use\n");
	print("it at your own risk.\n\n");
	print("Cheers,\nPhilip R. Simonson (aka 5n4k3)\n\n");
	print("Welcome to a bare bones kernel! This is a temporary shell.\n");
	print("Please type 'help' to see what you can do.\n\n> ");
}
/* Kernel process user input.
 */
void user_input(char *input)
{
	process_command(input);
	print("> ");
}
