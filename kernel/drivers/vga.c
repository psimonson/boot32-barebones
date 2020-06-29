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

/* Initialize the terminal (graphics).
 */
void terminal_initialize(void)
{
	vga_buffer = (unsigned short*)VGA_MEM;
	for(int y = 0; y < VGA_ROW; y++) {
		for(int x = 0; x < VGA_COL; x++) {
			terminal_putentryat(x, y, ' ', 0x0f);
		}
	}
}
/* Put a character on screen at given (x,y) coordinates.
 */
void terminal_putentryat(int x, int y, char ch, unsigned char color)
{
	if((x >= 0 && x < VGA_COL) && (y >= 0 && y < VGA_ROW)) {
		vga_buffer[y*VGA_COL+x] = (unsigned short)((color << 8) | ch);
	}
}
/* Print a string on screen at current location.
 */
void terminal_print(int x, int y, const char *s, unsigned char color)
{
	while(*s != '\0') {
		terminal_putentryat(x, y, *s, color);
		s++;
	}
}
