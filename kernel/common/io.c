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
#include "stdarg.h"

/* Print character to console.
 */
void _kputc(int col, int row, char c)
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
}
/* Print character for kernel.
 */
void kputc(char c)
{
	_kputc(-1, -1, c);
}
/* Print character for kernel.
 */
int _kputs(const char *s)
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
/* Print formatted for kernel.
 */
int kprintf(const char *format, ...)
{
	va_list ap;
	int i;
	
	va_start(ap, format);
	for(i = 0; i < strlen(format); ) {
		switch(format[i]) {
			case '%':
				switch(format[i+1]) {
					case 'c': {
						char c = va_arg(ap, char);
						kputc(c);
						i++;
						break;
					}
					case 's': {
						int c = (int)va_arg(ap, const char*);
						char str[32] = {0};
						itoa_s(c, 10, str, 32);
						i += kputs(str);
						i++;
						break;
					}
					case 'd':
					case 'i': {
						int c = va_arg(ap, int);
						char str[32] = {0};
						itoa_s(c, 10, str, 32);
						i += kputs(str);
						i++;
						break;
					}
					case 'x':
					case 'X': {
						int c = va_arg(ap, int);
						char str[32] = {0};
						itoa_s(c, 16, str, 32);
						i += kputs(str);
						i++;
						break;
					}
					default:
						return -1;
				}
			case '\\':
				switch(format[i+1]) {
					case 'n':
						kputs("\n");
						i++;
						break;
					break;
					case 'b':
						kputs("\b");
						i++;
						break;
					break;
					default:
						return -1;
				}
			break;
			default:
				kputc(format[i]);
				i++;
		}
	}
	va_end(ap);
	return i;
}
