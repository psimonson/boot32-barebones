# ========================================
# Simple boot32 barebones Makefile
# by Philip R. Simonson.
# ========================================

AS=nasm
AFLAGS=-f bin

SRCDIR=$(shell pwd)

PROJECT_NAME=$(shell basename $(SRCDIR))
PROJECT_VERSION=1.0

TARGETS=stage1.bin stage2.bin

.PHONY: all run disk clean distclean dist
all: $(TARGETS)

%.asm:
	$(AS) $(AFLAGS) $@

%.bin: %.asm
	$(AS) $(AFLAGS) -o $@ $<

run: clean disk
	qemu-system-i386 -fda floppy.img

disk: all
	dd if=/dev/zero of=floppy.img bs=512 count=2880
	dd if=stage1.bin of=floppy.img bs=512 count=1 conv=notrunc
	dd if=stage2.bin of=floppy.img bs=512 seek=1 conv=notrunc

clean:
	rm -f $(TARGETS)

distclean: clean
	rm -f floppy.img *.bak

dist: distclean
	cd .. && tar -cv --exclude=.git ./$(PROJECT_NAME) | xz -9 > $(PROJECT_NAME)-$(PROJECT_VERSION).tar.xz
