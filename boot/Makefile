# Bootloader makefile by Philip R. Simonson
AS=nasm
AFLAGS=-f bin

BACKUPS=$(shell find . -iname "*.bak")
INCLUDES=common.inc common32.inc a20.inc disk.inc

TARGETS=stage1.bin stage2.bin

.PHONY: all clean distclean
all: $(TARGETS)

%.bin: %.asm
	$(AS) $(AFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)

distclean:
ifneq ($(BACKUPS),)
	rm -f $(BACKUPS)
endif
