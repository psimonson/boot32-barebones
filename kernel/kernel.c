#include "vga.h"

void kernel_main(void)
{
	term_init(BLUE, YELLOW);
	kprint("Hello world, this is a simple kernel.\n");
}
