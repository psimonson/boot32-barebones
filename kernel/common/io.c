/*
 * io.c - Source file for standard output functions.
 *
 * Author: Philip R. Simonson
 * Date  : 07/01/2020
 *
 ****************************************************************
 */

#include <limits.h>

#include "vga.h"
#include "helper.h"
#include "stdarg.h"
#include "io.h"

/* Print character to console.
 */
static int _kputc(int col, int row, char c)
{
	int offset;
	
	if(col >= 0 && row >= 0) {
		offset = get_screen_offset(col, row);
	} else {
		offset = get_cursor_offset();
		row = get_offset_row(offset);
		col = get_offset_col(offset);
	}
	
	offset = print_char(col, row, c);
	row = get_offset_row(offset);
	col = get_offset_col(offset);
	return c;
}
/* Print character for kernel.
 */
int kputc(char c)
{
	return _kputc(-1, -1, c);
}
/* Print character for kernel.
 */
static int _kputs(const char *s)
{
	int i;
	for(i = 0; i < strlen(s); i++)
		kputc(s[i]);
	return i;
}
/* Print string to console.
 */
int kputs(const char *s)
{
	return _kputs(s);
}
/* Print character by character to screen with length.
 */
static int _kprint(const char *str, unsigned int len)
{
	const unsigned char *bytes = (const unsigned char *)str;
	for(unsigned int i = 0; i < len; i++)
		if(kputc(bytes[i]) == EOF)
			return 0;
	return 1;
}
/* Print formatted for kernel.
 */
int kprintf(const char *format, ...)
{
	va_list ap;
	int written = 0;
	
	va_start(ap, format);
	while(*format != 0) {
		unsigned maxrem = INT_MAX - written;
		
		if(format[0] != '%' || format[1] == '%') {
			if(format[0] == '%')
				format++;
			unsigned amount = 1;
			while(format[amount] && format[amount] != '%')
				amount++;
			if(maxrem < amount) {
				/* TODO: Set errno to EOVERFLOW. */
				return -1;
			}
			if(!_kprint(format, amount))
				return -1;
			format += amount;
			written += amount;
			continue;
		}
		
		const char *format_begun_at = format++;
		
		if(*format == 'c') { /* Character */
			format++;
			char c = (char)va_arg(ap, int);
			if(!maxrem) {
				/* TODO: Set errno to EOVERFLOW. */
				return -1;
			}
			kputc(c);
			written++;
		} else if(*format == 's') { /* String */
			format++;
			const char *str = va_arg(ap, const char*);
			unsigned len = strlen(str);
			if(maxrem < len) {
				/* TODO: Set errno to EOVERFLOW. */
				return -1;
			}
			if(!_kprint(str, len))
				return -1;
			written += len;
		} else if(*format == 'd' || *format == 'i') { /* Integer */
			format++;
			int c = va_arg(ap, int);
			char str[32] = {0};
			unsigned len;

			itoa_s(c, 10, str, 32);
			len = strlen(str);
			if(maxrem < len) {
				/* TODO: Set errno to EOVERFLOW. */
				return -1;
			}
			if(!_kprint(str, len))
				return -1;
			written += len;
		} else if(*format == 'x' || *format == 'X') { /* Hexadecimal */
			format++;
			int c = va_arg(ap, int);
			char str[32] = {0};
			unsigned len;

			itoa_s(c, 16, str, 32);
			len = strlen(str);
			if(maxrem < len) {
				/* TODO: Set errno to EOVERFLOW. */
				return -1;
			}
			if(!_kprint(str, len))
				return -1;
			written += len;
		} else { /* Normal character */
			format = format_begun_at;
			unsigned len = strlen(format);
			if(maxrem < len) {
				/* TODO: Set errno to EOVERFLOW. */
				return -1;
			}
			if(!_kprint(format, len))
				return -1;
			written += len;
			format += len;
		}
	}
	va_end(ap);
	return written;
}
