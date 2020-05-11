ASPARAMS = -f elf32
CPARAMS = -m32 -nostdlib -fno-builtin -fno-exceptions
%.o: %.c
	gcc $(CPPPARAMS) -o $@ -c $<
%.o: %.asm
	nasm $(ASPARAMS) -o $@ $<
mykernel.bin: linker.ld loader.o kernel.o
	ld -m elf_i386 -T $< -o $@ loader.o kernel.o
install: mykernel.bin
	cp $< /boot/mykernel.bin
clean:
	rm *.o *.out *.bin
