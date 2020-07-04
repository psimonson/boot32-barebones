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
	while(*s++ != '\0') i++;
	return i;
}
/* Compares two strings together.
 */
int strcmp(const char *s, const char *t)
{
	for( ; *s == *t; s++, t++)
		if(*s == '\0') return 0;
	return *s-*t;
}
/* Reverse a string in place.
 */
void reverse(char s[])
{
	char *p = s, *t = s+(strlen(s)-1);
	while(*p != *t) {
		char tmp = *p;
		*p = *t;
		*t = tmp;
		p++, t++;
	}
}
/* Convert integer to c-string.
 */
void itoa(int n, char s[], int size)
{
	int i, sign;
	if((sign = n) < 0) n = -n;
	for(i = 0; i < size && n > 0; n /= 10, ++i)
		s[i] = n % 10 + '0';
	if(i < size && sign < 0) s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* ----------------------- Helper Functions ---------------------- */

/* Append to kernel buffer.
 */
void append(char s[], char c)
{
	int len = strlen(s);
	s[len] = c;
	s[len+1] = '\0';
}
/* Backspace from the kernel buffer.
 */
void backspace(char s[])
{
	int len = strlen(s);
	s[len-1] = '\0';
}
