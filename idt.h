#ifndef IDT_H
#define IDT_H

extern struct gdt_entry idt;
extern struct gdt_ptr idtp;

void idt_install();

#endif
