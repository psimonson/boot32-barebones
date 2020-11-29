/*
 * helper.h - Miscellaneous functions for integers and strings.
 *
 * Author: Philip R. Simonson
 * Date  : 07/04/2020
 *
 ********************************************************************
 */

#include "helper.h"

/* ------------------------ Used internally ---------------------- */

char _itoa[32];

/* ----------------------- Helper Functions ---------------------- */

/* Get length of given string.
 */
int strlen(const char *s)
{
	int i = 0;
	while(s[i] != 0) i++;
	return i;
}
/* Strip off new line from string.
 */
int strstrip(char *s)
{
	int pos = strlen(s);
	while(--pos >= 0)
		if(s[pos] == '\n')
			s[pos] = 0;
	return pos;
}
/* Compares two strings together.
 */
int strcmp(const char *s, const char *t)
{
	int i;
	for(i = 0; s[i] == t[i]; i++)
		if(s[i] == 0)
			return 0;
	return s[i]-t[i];
}
/* Reverse a string in place.
 */
void reverse(char *s)
{
	const int len = strlen(s)-1;
	int i, j;
	for(i = 0, j = len; s[i] != s[j]; i++, j--) {
		char tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
}
/* Convert integer to c-string.
 */
void itoa(unsigned n, unsigned base, char *s, int size)
{
	int opos, pos;
	
	/* Check bounds */
	if(n == 0 || base > 16) {
		s[0] = '0';
		s[1] = 0;
		return;
	}
	
	/* Fill itoa buffer */
	for(pos = 0; n != 0; n /= 10, pos++)
		_itoa[pos] = n % base + '0';
	/* Read itoa buffer backwards */
	for(opos = 0; opos < size && pos != 0; pos--,opos++)
		s[opos] = _itoa[pos];
}
/* Convert integer to c-string safely.
 */
void itoa_s(int n, unsigned base, char *buf, int size)
{
	if(base > 16) return;
	if(n < 0) {
		buf[0] = '-';
		buf[1] = 0;
	} else {
		buf[0] = 0;
	}
	itoa(n, base, buf, size);
}

/* ----------------------- Helper Functions ---------------------- */

/* Append to kernel buffer.
 */
void append(char *s, char c)
{
	int len = strlen(s);
	s[len++] = c;
	s[len] = '\0';
}
/* Backspace from the kernel buffer.
 */
void backspace(char *s)
{
	int len = strlen(s);
	s[len-1] = '\0';
}
