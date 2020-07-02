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

.PHONY: all run debug disk clean distclean dist
all: $(TARGETS)
	cd ./kernel && make
	cd imagefs && make
	cd prsfs && make

%.asm:
	$(AS) $(AFLAGS) $@

stage1.bin: stage1.asm common.inc disk.inc
	$(AS) $(AFLAGS) -o $@ $<

stage2.bin: stage2.asm common.inc a20.inc
	$(AS) $(AFLAGS) -o $@ $<

run: clean disk
	qemu-system-i386 -fda floppy.img -boot a

debug: clean disk
	qemu-system-i386 -fda floppy.img -boot a -s &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel/kernel.elf"

disk: all
	imagefs/imagefs c floppy.img 2880
	imagefs/imagefs w floppy.img stage1.bin
	prsfs/prsfs floppy.img stage2.bin kernel/kernel.bin
#	dd if=/dev/zero of=floppy.img bs=512 count=2880
#	dd if=stage1.bin of=floppy.img bs=512 count=1 conv=notrunc
#	dd if=stage2.bin of=floppy.img bs=512 seek=1 conv=notrunc
#	dd if=kernel/kernel.bin of=floppy.img bs=512 seek=2 conv=notrunc

clean:
	rm -f $(TARGETS)
	cd ./kernel && make clean
	cd ./imagefs && make clean
	cd ./prsfs && make clean

distclean: clean
	rm -f floppy.img *.bak *.log
	cd ./kernel && make distclean
	cd ./imagefs && make distclean
	cd ./prsfs && make distclean

dist: distclean
	cd .. && tar -cv --exclude=.git ./$(PROJECT_NAME) | xz -9 > $(PROJECT_NAME)-$(PROJECT_VERSION).tar.xz
