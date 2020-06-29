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

#define VGA_MEM 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define get_offset(x,y) (2*((y)*MAX_COLS+(x)))
#define get_offset_row(x) ((x) / (2*MAX_COLS))
#define get_offset_col(x) (((x) - (get_offset_row((x))*2*MAX_COLS))/2)

static unsigned char *vga_buffer;
char _terminal_initialized;

/* Prototypes for private functions. */
int print_char(int col, int row, char ch, char attr);
int get_cursor_offset(void);
void set_cursor_offset(int offset);

/* Initialize the terminal (graphics).
 */
void clear_screen(const char attr)
{
	int screen_size = MAX_COLS * MAX_ROWS;

	if(!_terminal_initialized) {
		term_init(attr);
		return;
	}

	for(int i = 0; i < screen_size; i++) {
		vga_buffer[i*2] = ' ';
		vga_buffer[i*2+1] = attr;
	}
}
/* Initialize the terminal.
 */
void term_init(const char attr)
{
	if(!_terminal_initialized) {
		_terminal_initialized = 1;
		vga_buffer = (unsigned char *)VGA_MEM;
		clear_screen(attr);
	}
}
/* Print a string on screen at given (x,y) position.
 */
void kprint_at(int col, int row, const char *s, char attr)
{
	int offset;

	if(col >= 0 && row >= 0)
		offset = get_offset(col, row);
	else {
		offset = get_cursor_offset();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}

	/* Loop through message and print it */
	for(int i = 0; s[i] != '\0'; i++) {
		offset = print_char(col, row, s[i], attr);
		/* Compute row/col for next iteration */
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
}
/* Print a string on screen at current location.
 */
void kprint(const char *s, char attr)
{
	kprint_at(-1, -1, s, attr);
}

/* ------------------------- Private Functions -------------------------- */

/* Put a character on the screen at given location.
 */
int print_char(int col, int row, char c, char attr)
{
	if(attr < 0) attr = YELLOW_ON_BLUE;

	/* Error control: print red 'E' if the coordinates aren't right. */
	if(col >= MAX_COLS || row >= MAX_ROWS) {
		vga_buffer[2*MAX_COLS*MAX_ROWS-2] = 'E';
		vga_buffer[2*MAX_COLS*MAX_ROWS-2-1] = RED_ON_BLUE;
		return get_offset(col, row);
	}

	int offset;
	if(col >= 0 && row >= 0) offset = get_offset(col, row);
	else offset = get_cursor_offset();

	if(c == '\n') {
		row = get_offset_row(offset);
		offset = get_offset(0, row+1);
	} else {
		vga_buffer[offset] = c;
		vga_buffer[offset+1] = attr;
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
	return offset *2; /* Position * size of character cell */
}
/* Set cursor position on the screen.
 */
void set_cursor_offset(int offset)
{
	offset /= 2;
	outb(REG_VGA_CTRL, 14);
	outb(REG_VGA_DATA, (unsigned char)(offset >> 8));
	outb(REG_VGA_CTRL, 15);
	outb(REG_VGA_DATA, (unsigned char)(offset & 0xff));
}
