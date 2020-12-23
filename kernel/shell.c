/*
 * shell.c - Source file for a simplistic shell.
 *
 * Author: Philip R. Simonson
 * Date  : 07/07/2020
 *
 *********************************************************************
 */

#include <stdbool.h>

#include "vga.h"
#include "helper.h"
#include "io.h"
#include "shell.h"
#include "pit.h"
#include "system.h"
#include "regs.h"

/* Login active external variable */
extern bool login_active;
extern bool regs_update;

/* Command structure */
typedef struct command {
	char *cmd;
	char *help;
	void (*func)(void);
} command_t;

/* Some macros for conversion */
#define TO_STR(c) #c
#define TO_CMD(c) cmd_ ##c

/* Some macros for building commands */
#define BEG_CMD const command_t commands[] = {
#define ADD_CMD(c,h) 	{ #c, h, &cmd_ ##c }
#define END_CMD };
#define CNT_CMD const int cmd_total = \
	sizeof(commands)/sizeof(command_t);

/* Macro to define command function */
#define DEF_FNC(c) void cmd_ ##c(void)

/* Prototypes for commands */
DEF_FNC(clear);
DEF_FNC(regs);
DEF_FNC(logout);
DEF_FNC(version);
DEF_FNC(help);
DEF_FNC(exit);

/* ----------------------------- Commands -------------------------- */

BEG_CMD
ADD_CMD(clear, "Clear the VGA screen buffer."),
ADD_CMD(regs, "Display register values."),
ADD_CMD(logout, "Log out of the operating system."),
ADD_CMD(version, "Displays the version information."),
ADD_CMD(help, "Display this help text."),
ADD_CMD(exit, "Halt execution of CPU.")
END_CMD
CNT_CMD

/* ----------------------------- Functions ------------------------- */

/* Clear command, erase VGA screen buffer.
 */
DEF_FNC(clear)
{
	clear_screen();
}
/* Regs command, display register values.
 */
DEF_FNC(regs)
{
	regs_t *regs;

	// Update register values and get regsters.
	regs = get_current_regs(true);

	// Display results.
	kprintf("List of registers below...\n");
	kprintf("==========================\n");
	kprintf("EAX: 0x%x\nEBX: 0x%x\nECX: 0x%x\nEDX: 0x%x\nESI: 0x%x\nEDI: 0x%x\n",
		regs->eax, regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi);
}
/* Logout command, quit the shell and return to login screen.
 */
DEF_FNC(logout)
{
	kprintf("Logging out...\n");
	sleep(1);
	kprintf("OK.\n");
	login_active = true;
	sound(500);
	delay(8);
	sound(0);
	sleep(1);
	clear_screen();
	kprintf("LOGIN? ");
}
/* Version command, display version information.
 */
DEF_FNC(version)
{
	const char msg[] = "Version 1.1!";
	kprintf("Barebones Operating System ");
	for(int i = 0; i < strlen(msg); i++) {
		kputc(msg[i]);
		sound(1000);
		delay(5);
		sound(0);
		delay(10);
	}
	kprintf("\nDate created: June 25, 2020.\n");
	kprintf("Written by Philip R. Simonson.\n\n");
	kprintf("Others helped me to fix the code I made, just \n");
	kprintf("a few fixes here and there. But, for the most \n");
	kprintf("part it is all my code.\n");
}
/* Help command, display help.
 */
DEF_FNC(help)
{
	kprintf("*** Available Commands ***\n");
	for(int i = 0; i < cmd_total; i++)
		kprintf("%s - %s\n", commands[i].cmd, commands[i].help);
}
/* Exit command, halt CPU.
 */
DEF_FNC(exit)
{
	kprintf("Halting CPU...\n");
	disable();
	halt();
}
/* Process user input.
 */
void process_command(char *input)
{
	for(int i = 0; i < cmd_total; i++) {
		if(!strcmp(commands[i].cmd, input)) {
			commands[i].func();
			return;
		}
	}
	kprintf("Invalid command entered.\n");
}
