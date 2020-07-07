/*
 * helper.h - Miscellaneous functions for integers and strings.
 *
 * Author: Philip R. Simonson
 * Date  : 07/04/2020
 *
 ********************************************************************
 */

#include "helper.h"

/* ----------------------- Helper Functions ---------------------- */

/* Get length of given string.
 */
int strlen(const char *s)
{
	int i = 0;
	while(s[i++] != '\0');
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
void reverse(char *s, int len)
{
	int i, j;
	for(i = 0, j = len-1; s[i] != s[j]; i++, j--) {
		char tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
}
/* Convert integer to c-string.
 */
void itoa(int n, char *s, int size)
{
	int i, sign;
	if((sign = n) < 0) n = -n;
	for(i = 0; i < size-1 && n > 0; n /= 10, i++)
		s[i++] = n % 10 + '0';
	if(i < size && sign < 0) s[i++] = '-';
	s[i] = '\0';
	reverse(s, i);
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
