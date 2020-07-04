/*
 * Author: Philip R. Simonson
 * Date  : 07/01/2020
 *
 ****************************************************************
 */

#include "vga.h"

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
