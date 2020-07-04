/*
 * vga.h - Header file for a very simple VGA graphics driver.
 *
 * Author: Philip R. Simonson
 * Date  : 06/27/2020
 *
 **********************************************************************
 */

#ifndef _VGA_H_
#define _VGA_H_

#define VGA_ADDRESS 0xB8000

#define MAX_ROWS 25
#define MAX_COLS 80

#define REG_VGA_CTRL 0x3d4
#define REG_VGA_DATA 0x3d5

/* Colors for foreground and background. */
enum vga_color { BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN,
GREY, DARK_GREY, BRIGHT_BLUE, BRIGHT_GREEN, BRIGHT_CYAN, BRIGHT_RED,
BRIGHT_MAGENTA, YELLOW, WHITE };

/* VGA memory buffer. */
unsigned char *vga_buffer;

/* Terminal initialization. */
void term_init(unsigned char bg, unsigned char fg);
/* Put a character on the screen. */
int print_char(int x, int y, char c);
/* Clear the screen. */
void clear_screen(void);
/* Set a new text attribute. */
void set_text_attr(unsigned char bg, unsigned char fg);
/* Get screen offset from (col, row). */
int get_screen_offset(int col, int row);
/* Get row from offset. */
int get_offset_row(int offset);
/* Get column from offset. */
int get_offset_col(int offset);
/* Get cursor offset. */
int get_cursor_offset(void);
/* Set cursor offset. */
void set_cursor_offset(int offset);

#endif
