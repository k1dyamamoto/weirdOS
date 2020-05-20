#ifndef GDT_H
#define GDT_H

extern struct gdt_entry gdt;
extern struct gdt_ptr gp;

void gdt_install();

#endif
