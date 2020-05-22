global gdt_flush
global idt_load 

extern gp          
extern idtp

; load new gdt (ds and cs with far jump)
gdt_flush:
	lgdt [gp]      
    	mov ax, 0x10    
    	mov ds, ax
    	mov es, ax
    	mov fs, ax
    	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2  
flush2:
	ret 

; load new idt
idt_load:
	lidt [idtp]
	ret

