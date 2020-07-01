AS=nasm
AFLAGS=-f elf32
CC=gcc
CFLAGS=-std=c11 -Wall -O -pedantic -g -m32 \
       -ffreestanding -fno-pie -fno-pic \
       -nostdlib -nostdinc -nostartfiles \
			 -I./drivers
LDFLAGS=
BACKUPS=$(shell find . -iname "*.bak")
OBJECTS=entry.o kernel.o io.o drivers/ports.o drivers/vga.o
TARGET=kernel.bin

.PHONY: all clean distclean
all: $(TARGET) kernel.elf

entry.o: entry.asm
	$(AS) $(AFLAGS) -o $@ $^

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -Tlink.ld -o $@ $^ --oformat binary

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -Tlink.ld -o $@ $^

clean:
	rm -f $(OBJECTS) $(TARGET) *.elf

distclean: clean
ifneq ($(BACKUPS),)
	rm -f $(BACKUPS)
endif
