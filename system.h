#ifndef SYSTEM_H
#define SYSTEM_H

enum  {	BLACK = 0x0000, 
	BLUE = 0x1000, 
	GREEN = 0x2000, 
	WHITE = 0xF000, 
	PURPLE = 0x5000, 
	RED = 0x4000, 
	YELLOW = 0xE000   };


extern unsigned char kbdus[128];
extern unsigned short *video_out;
extern unsigned short font_color;
struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

extern int cur_line();
extern void print(char *str);
extern void putc(unsigned char c);
extern void set_bg_color(unsigned short color);
extern void change_font_color(unsigned short color);
extern void keyboard_handler(struct regs *r);
extern void keyboard_install();
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short segment, unsigned char flags);

extern void isrs_install();
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();

extern struct gdt_entry idt;
extern struct gdt_ptr idtp;

extern void idt_install();


extern struct gdt_entry gdt;
extern struct gdt_ptr gp;

extern void gdt_install();

#endif
