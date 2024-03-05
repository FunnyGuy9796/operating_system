#include "kernel.h"

void main(unsigned long magic, unsigned long addr) {
	struct multiboot_tag *tag;
	init_terminal();
	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		kerror("Invalid magic number: %x\n", (unsigned) magic);
		return;
	}
	if (addr & 7) {
		kerror("Unaligned mbi: %x\n", addr);
		return;
	}
	init_gdt();
	
	printf("Welcome to OS\n");
}