/*
 * util.c - Common utility functions.
 *
 * Author: Philip R. Simonson
 * Date  : 07/03/2020
 *
 **************************************************************
 */

#include "util.h"

/* Copies memory from source to destination, using specified number of bytes.
 */
void memcpy(void *dest, const void *src, unsigned long bytes)
{
	char *d = (char*)dest;
	char *s = (char*)src;
	while(bytes-- > 0) {
		*d = *s;
		d++, s++;
	}
}
/* Convert integer to c-string.
 */
void itoa(int n, char *s, int size)
{
	int i, sign;

	if((sign = n) < 0)
		n = -n;

	for(i = 0; i < size && n > 0; n /= 10)
		s[i++] = n % 10 + '0';
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	/* TODO: Implement reverse and use it here. */
}
