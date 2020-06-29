#include "vga.h"

void kernel_main(void)
{
	terminal_initialize();
	terminal_print("Hello world, this is a simple kernel.", 0x1b);
}
