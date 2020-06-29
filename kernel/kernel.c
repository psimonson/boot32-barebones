#include "vga.h"

void kernel_main(void)
{
	terminal_initialize();
	terminal_print(0, 0, "Hello world, this is a simple kernel.", 0x0f);
	for(;;);
}
