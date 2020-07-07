/*
 * io.c - Source file for standard output functions.
 *
 * Author: Philip R. Simonson
 * Date  : 07/01/2020
 *
 ****************************************************************
 */

#include "vga.h"
#include "helper.h"

/* Print a string on screen at given (x,y) position.
 */
void print_at(int col, int row, char *s)
{
	int offset;

	if(col >= 0 && row >= 0) {
		offset = get_screen_offset(col, row);
	} else {
		offset = get_cursor_offset();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}

	for(int i = 0; s[i] != 0; i++) {
		offset = print_char(col, row, s[i]);
		/* Compute row/col for next iteration */
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}
/* Print a string on screen at current location.
 */
void print(char *s)
{
	print_at(-1, -1, s);
}
/* Print backspace character to screen.
 */
void print_bkspc(void)
{
	int offset = get_cursor_offset()-2;
	int row = get_offset_row(offset);
	int col = get_offset_col(offset);
	print_char(col, row, 0x08);
}
/* Print hex number to screen.
 */
void print_hex(unsigned int n)
{
	const char hex_digit[] = "0123456789ABCDEF";
	char buf[12] = {'0', 'x', '0'};
	int i;
	for(i = 2; i < 10; i++) {
		buf[i] = hex_digit[n%16];
		n /= 16;
	}
	buf[i] = 0;
	reverse(buf+2);
	print(buf);
}
