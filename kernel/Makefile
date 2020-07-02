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

$(TARGET): kernel.elf
	objcopy -O binary kernel.elf $(TARGET)

kernel.elf: $(OBJECTS) link.ld
	$(LD) $(LDFLAGS) -Tlink.ld -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) *.elf

distclean: clean
ifneq ($(BACKUPS),)
	rm -f $(BACKUPS)
endif
