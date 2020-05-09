CPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore
ASPARAMS = -f elf32
%.o: %.cpp
	g++ $(CPPPARAMS) -o $@ -c $<
%.o: %.asm
	nasm $(ASPARAMS) -o $@ $<
mykernel.bin: linker.ld loader.o kernel.o
	ld -m elf_i386 -T $< -o $@ loader.o kernel.o
install: mykernel.bin
	cp $< /boot/mykernel.bin
