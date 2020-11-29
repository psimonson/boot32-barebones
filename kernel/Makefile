AS=nasm
AFLAGS=-f elf32
CC=gcc
CFLAGS=-std=c11 -Wall -O -pedantic -g -m32 \
	-ffreestanding -fno-pie -fno-pic -fno-builtin \
	-nostdlib -nostartfiles \
	-I. -I./drivers -I./common -I./cpu
LDFLAGS=
BACKUPS=$(shell find . -iname "*.bak")
OBJECTS=kernel.o shell.o common/io.o common/helper.o \
	common/util.o drivers/vga.o drivers/keyboard.o \
	cpu/idt.o cpu/isr.o cpu/int.o cpu/ports.o cpu/timer.o
TARGET=kernel.bin

.PHONY: all clean distclean
all: $(TARGET) kernel.elf

%.o: %.asm
	$(AS) $(AFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

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
