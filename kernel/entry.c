/*
 * entry.c - Main entry point for this operating system.
 *
 * Author: Philip R. Simonson
 * Date: 12/12/2020
 *
 **********************************************************************
 */

#include <stdbool.h>

/* Some global external variables */
extern void kernel_main(void);
extern bool kbd_istyping;
extern bool login_active;

/* Start of operating system.
 */
void _start(void)
{
	// Initialize variables and start main routine
	kbd_istyping = false;
	login_active = true;
	kernel_main();
}
