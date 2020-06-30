/*
 * vga.c - Source file containing a simple VGA video driver.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 ********************************************************************
 */

#include "vga.h"
#include "ports.h"

#define MAX_ROWS 25
#define MAX_COLS 80

static unsigned char *vga_buffer;
static unsigned char _text_attr = 0, _term_init = 0;

/* Prototypes for private functions. */
int print_char(int col, int row, char ch);
int get_cursor_offset(void);
void set_cursor_offset(int offset);

/* Get offset for screen.
 */
int get_screen_offset(int col, int row)
{
	return 2 * (row * MAX_COLS + col);
}
/* Get offset for rows.
 */
int get_offset_row(int offset)
{
	return offset / (2 * MAX_COLS);
}
/* Get offset for columns.
 */
int get_offset_col(int offset)
{
	return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}
/* Make text attribute from foreground and background.
 */
unsigned char make_attr(unsigned char bg, unsigned char fg)
{
	return ((bg << 4) | fg);
}
/* Set color text attribute.
 */
void set_text_attr(unsigned char bg, unsigned char fg)
{
	_text_attr = make_attr(bg, fg);
}
/* Initialize the terminal (graphics).
 */
void clear_screen(void)
{
	int col = 0, row = 0;

	if(!_term_init) return;

	for(int x = 0; x < MAX_COLS; x++) {
		for(int y = 0; y < MAX_ROWS; y++) {
			int offset = print_char(col, row, ' ');
			row = get_offset_row(offset);
			col = get_offset_col(offset);
		}
	}

	set_cursor_offset(get_screen_offset(0, 0));
}
/* Initialize the terminal.
 */
void term_init(unsigned char bg, unsigned char fg)
{
	if(!_term_init) {
		_term_init = 1;
		vga_buffer = (void*)VGA_ADDRESS;
		_text_attr = make_attr(bg, fg);;
		clear_screen();
	}
}
/* Print a string on screen at given (x,y) position.
 */
void kprint_at(int col, int row, const char *s)
{
	int offset;

	if(col >= 0 && row >= 0)
		offset = get_screen_offset(col, row);
	else {
		offset = get_cursor_offset();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}

	/* Loop through message and print it */
	for(int i = 0; s[i] != 0; i++) {
		offset = print_char(col, row, s[i]);
		/* Compute row/col for next iteration */
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}
/* Print a string on screen at current location.
 */
void kprint(const char *s)
{
	kprint_at(-1, -1, s);
}

/* ------------------------- Private Functions -------------------------- */

/* Put a character on the screen at given location.
 */
int print_char(int col, int row, char c)
{
	int offset;
	if(col >= 0 && row >= 0) {
		offset = get_screen_offset(col, row);
	} else {
		offset = get_cursor_offset();
	}

	if(c == '\n') {
		int row = get_offset_row(offset);
		offset = get_screen_offset(0, row+1);
	} else {
		vga_buffer[offset] = c;
		vga_buffer[offset+1] = _text_attr;
		offset += 2;
	}
	set_cursor_offset(offset);
	return offset;
}
/* Get cursor position on the screen.
 */
int get_cursor_offset(void)
{
	outb(REG_VGA_CTRL, 14);
	int offset = inb(REG_VGA_DATA) << 8;
	outb(REG_VGA_CTRL, 15);
	offset += inb(REG_VGA_DATA);
	return offset * 2; /* Position * size of character cell */
}
/* Set cursor position on the screen.
 */
void set_cursor_offset(int offset)
{
	offset /= 2;
	outb(REG_VGA_CTRL, 14);
	outb(REG_VGA_DATA, (unsigned char)(offset >> 8));
	outb(REG_VGA_CTRL, 15);
	outb(REG_VGA_DATA, (unsigned char)offset);
}
