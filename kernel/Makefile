AS=nasm
AFLAGS=-f elf32
CC=gcc
CFLAGS=-std=c11 -Wall -O -pedantic -g -m32 \
	-ffreestanding -fno-pie -fno-pic -fno-builtin \
	-nostdlib -Wno-multichar -nostartfiles \
	-I. -I./drivers -I./common -I./cpu
LDFLAGS=
BACKUPS=$(shell find . -iname "*.bak")
OBJECTS=entry.asm.o cpu/int.asm.o cpu/gen_interrupt.asm.o
OBJECTS+=\
	kernel.c.o shell.c.o common/io.c.o common/helper.c.o \
	common/util.c.o drivers/vga.c.o drivers/keyboard.c.o \
	cpu/idt.c.o cpu/isr.c.o	cpu/system.c.o cpu/ports.c.o \
	cpu/pit.c.o cpu/hal.c.o cpu/cpu.c.o cpu/gdt.c.o \
	cpu/pic.c.o
TARGET=kernel.bin

.PHONY: all clean distclean
all: $(TARGET)

%.asm:

%.asm.o: %.asm
	$(AS) $(AFLAGS) -o $@ $<

%.c.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): kernel.elf
	objcopy -O binary kernel.elf $@

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -Tlink.ld -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) *.elf

distclean: clean
ifneq ($(BACKUPS),)
	rm -f $(BACKUPS)
endif
