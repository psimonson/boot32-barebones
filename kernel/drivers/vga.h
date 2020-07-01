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

/* Initialize the terminal (Text Video Mode). */
void term_init(unsigned char fg, unsigned char bg);
/* Print a string on screen at given (x, y). */
void kprint_at(int x, int y, const char *s);
/* Print a string on screen at current position. */
void kprint(const char *s);
/* Clear the screen. */
void clear_screen(void);
/* Set a new text attribute. */
void set_text_attr(unsigned char bg, unsigned char fg);
/* Make a text attribute. */
unsigned char make_attr(unsigned char bg, unsigned char fg);

#endif
