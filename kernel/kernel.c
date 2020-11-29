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
#include "helper.h"
#include "io.h"
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
	kprintf("Please type 'help' to see what you can do.\n\n> ");
}
/* Kernel process user input.
 */
void user_input(char *input)
{
	process_command(input);
	kprintf("> ");
}
/* Start of operating system.
 */
 void _start(void)
 {
 	kernel_main();
 }
