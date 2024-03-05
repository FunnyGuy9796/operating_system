#include "kernel.h"

void main(unsigned long magic, unsigned long addr) {
	init_terminal();
	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		kerror("Invalid magic number: 0x%x\n", (unsigned) magic);
		return;
	}
	if (addr & 7) {
		kerror("Unaligned mbi: 0x%x\n", addr);
	}
	init_gdt();
	printf("Welcome to OS\n");
}