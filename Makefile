CC = $(HOME)/cross/bin/i686-elf-gcc
AS = $(HOME)/cross/bin/i686-elf-as
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASFLAGS = 

SRCS := $(wildcard *.c) $(wildcard *.s)
OBJS = $(SRCS:.c=.o)

TARGET = os.bin

LINKER_SCRIPT = linker.ld
OBJ_LINK_LIST:=$(OBJS)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ_LINK_LIST)
	$(CC) -T $(LINKER_SCRIPT) -o $@ -ffreestanding -O2 -nostdlib $(OBJ_LINK_LIST) -lgcc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
