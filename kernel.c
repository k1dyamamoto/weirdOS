#include "gdt.h"
#include "visual.h"

void kernelMain()
{
	gdt_install();
	set_bg_color(BLACK);
	change_font_color(YELLOW);
	print("Welcome!:");
	
	while(1);
}
