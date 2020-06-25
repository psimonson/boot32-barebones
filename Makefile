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

.PHONY: all run clean distclean dist
all: $(TARGETS)

%.asm:
	$(AS) $(AFLAGS) $@

%.bin: %.asm
	$(AS) $(AFLAGS) -o $@ $<

run: clean all
	qemu-system-i386 stage1.bin

clean:
	rm -f $(TARGETS)

distclean: clean
	rm -f *.bak

dist: distclean
	cd .. && tar -cv --exclude=.git ./$(PROJECT_NAME) | xz -9 > $(PROJECT_NAME)-$(PROJECT_VERSION).tar.xz
