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
/* Compares two strings together.
 */
int strcmp(const char *s, const char *t)
{
	int i;
	for(i = 0; s[i] == t[i]; i++)
		if(s[i] != '\0') return 0;
	return s[i] - t[i];
}
/* Reverse a string in place.
 */
void reverse(char *s)
{
	for(int i = 0, j = strlen(s)-1; i != j; i++, j--) {
		char tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
}
/* Convert integer to c-string.
 */
void itoa(int n, char *s)
{
	int i, sign;
	if((sign = n) < 0) n = -n;
	i = 0;
	do{
		s[i++] = n % 10 + '0';
	} while((n /= 10) > 0);
	if(sign < 0) s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

/* ----------------------- Helper Functions ---------------------- */

/* Append to kernel buffer.
 */
void append(char *s, char c)
{
	int len = strlen(s);
	s[len] = c;
	s[len+1] = '\0';
}
/* Backspace from the kernel buffer.
 */
void backspace(char *s)
{
	int len = strlen(s);
	s[len-1] = '\0';
}
