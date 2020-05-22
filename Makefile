ASPARAMS = -f elf32
CPARAMS = -m32 -nostdlib -fno-builtin -fno-exceptions
OBJECTS = loader.o kernel.o gdt.o idt.o visual.o loadregs.o
%.o: %.c
	gcc $(CPPPARAMS) -o $@ -c $<
%.o: %.asm
	nasm $(ASPARAMS) -o $@ $<
mykernel.bin: linker.ld $(OBJECTS) 
	ld -m elf_i386 -T $< -o $@ $(OBJECTS)
install: mykernel.bin
	cp $< /boot/mykernel.bin
clean:
	rm *.o *.out *.bin
