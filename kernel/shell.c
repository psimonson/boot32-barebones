/*
 * shell.c - Source file for a simplistic shell.
 *
 * Author: Philip R. Simonson
 * Date  : 07/07/2020
 *
 *********************************************************************
 */

#include "vga.h"
#include "helper.h"
#include "io.h"
#include "shell.h"

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
DEF_FNC(help);
DEF_FNC(exit);

/* ----------------------------- Commands -------------------------- */

BEG_CMD
ADD_CMD(clear, "Clear the VGA screen buffer."),
ADD_CMD(regs, "Display register values."),
ADD_CMD(help, "Display this help text."),
ADD_CMD(exit, "Halt execution of CPU.")
END_CMD
CNT_CMD

/* ----------------------------- Functions ------------------------- */

/* Clear command, erase VGA screen buffer.
 */
DEF_FNC(clear) {
	clear_screen();
}
/* Regs command, display register values.
 */
DEF_FNC(regs) {
	unsigned int eax, ebx, ecx, edx, esi, edi;
	__asm__ __volatile__("" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx));
	__asm__ __volatile__("" : "=S"(esi), "=D"(edi));
	kprintf("List of registers below...\n");
	kprintf("==========================\n");
	kprintf("EAX: %x\nEBX: %x\nECX: %x\nEDX: %x\nESI: %x\nEDI: %x\n",
		eax, ebx, ecx, edx, esi, edi);
}
/* Help command, display help.
 */
DEF_FNC(help) {
	kprintf("*** Available Commands ***\n");
	for(int i = 0; i < cmd_total; i++)
		kprintf("%s - %s\n", commands[i].cmd, commands[i].help);
}
/* Exit command, halt CPU.
 */
DEF_FNC(exit) {
	kprintf("Halting CPU...\n");
	__asm__ __volatile__("cli");
	__asm__ __volatile__("hlt");
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
