#include "vga.h"

void kernel_main(void)
{
	term_init(BLUE, YELLOW);
//	kprint("Hello world, this is a simple kernel.\n");
	vga_buffer[0] = 'X';
	vga_buffer[1] = make_attr(BLUE, YELLOW);
}
