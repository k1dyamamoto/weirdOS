MAGIC equ 0x1badb002
FLAGS equ (0<<1 | 1<<1)
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
        dd MAGIC
        dd FLAGS
        dd CHECKSUM

section .bss
section .text
	extern kernelMain
	global loader

loader:
        mov esp, 4096
        call kernelMain

