AS=nasm
AFLAGS=-f elf32
CC=gcc
CFLAGS=-std=c11 -Wall -O -pedantic -g -m32 \
       -ffreestanding -fno-pie -fno-pic \
       -nostdlib -nostdinc -nostartfiles \
       -I./include
LDFLAGS=-m elf_i386 -Ttext 0x1000
OBJECTS=entry.o kernel.o drivers/vga.o
TARGET=kernel.bin

.PHONY: all clean distclean
all: $(TARGET)

entry.o: entry.asm
	$(AS) $(AFLAGS) -o $@ $^

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o kernel.elf $^
	objcopy -O binary kernel.elf $@

clean:
	rm -f $(OBJECTS) $(TARGET) *.elf

distclean: clean
	rm -f *.bak
