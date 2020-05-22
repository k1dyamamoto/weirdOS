struct idt_entry
{
	unsigned short base_low;
    	unsigned short segment;       
    	unsigned char zero;    
	unsigned char flags;       
	unsigned short base_high;
} __attribute__((packed));

struct idt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load();

void idt_set_gate(unsigned char num, unsigned long base, unsigned short segment, unsigned char flags)
{
	idt[num].base_low = (base & 0xFFFF);
    	idt[num].base_high = (base >> 16) & 0xFFFF;
    	idt[num].segment = segment;
	idt[num].zero = 0;
    	idt[num].flags = flags;
}

void idt_install()
{
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    	idtp.base = &idt;
	
	// clear idt
	char *temp = (char *)(&idt);
	int size = sizeof(struct idt_entry) * 256;
	for (int i = 0; i < size; i++)
		*(temp + i) = 0; 
    	
    	idt_load();
}
