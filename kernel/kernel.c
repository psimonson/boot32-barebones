#include "vga.h"
#include "io.h"

void kernel_main(void)
{
	term_init(BLUE, YELLOW);
	print("Welcome to my bare bones example 32 bit operating system.\n");
	print("\n  I have designed this because I would like to teach beginners\n");
	print("the proper way of doing things. As far as a beginning operating\n");
	print("system goes. Please feel free to clone and use it. If you are\n");
	print("are worried about a LICENSE don't be. I will NOT put a LICENSE\n");
	print("on this project. Also this software comes WITHOUT ANY WARRANTY\n");
	print("of any kind. I will not be held accountable for any damage this\n");
	print("software may cause. Please use at your own risk.\n");
	print("\n\nCheers,\nPhilip R. Simonson (aka 5n4k3)\n"); 
}
