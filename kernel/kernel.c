#include "vga.h"
#include "io.h"

void kernel_main(void)
{
	term_init(BLUE, YELLOW);
        print("Hello World!\n");
}
