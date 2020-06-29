#include "vga.h"

void kernel_main(void)
{
	term_init(YELLOW_ON_BLUE);
	kprint("Hello world, this is a simple kernel.\n", YELLOW_ON_BLUE);
}
