#include "system.h"

void kernelMain()
{
	gdt_install();
	idt_install();
	isrs_install();
    	irq_install();
	keyboard_install();
	__asm__ __volatile__ ("sti");
	set_bg_color(BLACK);
	change_font_color(YELLOW);
	print("Welcome!:");
	
	while(1);
}
