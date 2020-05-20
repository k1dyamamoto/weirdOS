MAGIC equ 0x1badb002
FLAGS equ (0<<1 | 1<<1)
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
        dd MAGIC
        dd FLAGS
        dd CHECKSUM

section .text
	extern kernelMain
	global loader

loader:
        mov esp, kernel_stack
        call kernelMain
section .bss
resb 4 * 1024 * 1024
kernel_stack:
