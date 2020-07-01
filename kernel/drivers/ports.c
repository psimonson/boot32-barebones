#include "ports.h"

/* Get byte from given port.
 */
unsigned char inb(unsigned short port)
{
	unsigned char value;
	__asm__ __volatile__("in %%dx, %%al" : "=a"(value) : "d"(port));
	return value;
}
/* Put byte to given port.
 */
void outb(unsigned short port, unsigned char value)
{
	__asm__ __volatile__("out %%al, %%dx" : : "a"(value), "d"(port));
}
/* Get short from given port.
 */
unsigned short inw(unsigned short port)
{
	unsigned short value;
	__asm__ __volatile__("in %%dx, %%ax" : "=a"(value) : "d"(port));
	return value;
}
/* Put short to given port.
 */
void outw(unsigned short port, unsigned short value)
{
	__asm__ __volatile__("out %%ax, %%dx" : : "a"(value), "d"(port));
}
