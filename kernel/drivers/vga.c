/*
 * vga.c - Source file containing a simple VGA video driver.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 ********************************************************************
 */

#include "vga.h"

#define VGA_MEM 0xb8000
#define VGA_ROW 25
#define VGA_COL 80

static unsigned short *vga_buffer;
static long unsigned terminal_row;
static long unsigned terminal_col;

/* Initialize the terminal (graphics).
 */
void terminal_initialize(void)
{
	vga_buffer = (unsigned short*)VGA_MEM;
	terminal_col = 0;
	terminal_row = 0;

	for(int y = 0; y < VGA_ROW; y++) {
		for(int x = 0; x < VGA_COL; x++) {
			terminal_putc(' ', 0x0f);
		}
	}
}
/* Put a character on screen at given (x,y) coordinates.
 */
void terminal_putentryat(int x, int y, char ch, unsigned char color)
{
	if((x >= 0 && x < VGA_COL) && (y >= 0 && y < VGA_ROW)) {
		const long unsigned index = terminal_row*VGA_COL+terminal_col;
		vga_buffer[index] = (unsigned short)((color << 8) | ch);
	}
}
/* Put a character on the screen at current location.
 */
void terminal_putc(char ch, unsigned char color)
{
	switch(ch) {
		case '\n':
			terminal_col = 0;
			terminal_row++;
		break;
		default:
			terminal_putentryat(terminal_col, terminal_row, ch, color);
			terminal_col++;
		break;
	}

	if(terminal_col >= VGA_COL) {
		terminal_col = 0;
		terminal_row++;
	}

	if(terminal_row >= VGA_ROW) {
		terminal_col = 0;
		terminal_row = 0;
	}
}
/* Print a string on screen at current location.
 */
void terminal_print(const char *s, unsigned char color)
{
	while(*s != '\0') {
		terminal_putc(*s, color);
		s++;
	}
}
/* Enable the cursor.
 */
void terminal_cursor_on(void)
{
}
/* Disable the cursor.
 */
void terminal_cursor_off(void)
{
}
