#include "ports.h"

/* Get value from given port.
 */
unsigned char inb(unsigned short port)
{
	unsigned char value;
	__asm__ __volatile__("inb %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}
/* Put value to given port.
 */
void outb(unsigned short port, unsigned char value)
{
	__asm__ __volatile__("outb %1, %0" : : "Nd"(port), "a"(value));
}
