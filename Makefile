# ========================================
# Simple boot32 barebones Makefile
# by Philip R. Simonson.
# ========================================

AS=nasm
AFLAGS=-f bin

# Custom commands
IMAGEFS=./imagefs/imagefs
PRSFS=./prsfs/prsfs

SRCDIR=.

PROJECT_DIR=$(shell pwd)
PROJECT_NAME=$(shell basename $(PROJECT_DIR))
PROJECT_VERSION=1.0

CDROM_IMG=$(SRCDIR)/boot32-barebones.iso

.PHONY: all run debug disk clean distclean dist
all:
	cd $(SRCDIR)/boot && make
	cd $(SRCDIR)/kernel && make
	cd $(SRCDIR)/imagefs && make
	cd $(SRCDIR)/prsfs && make

run: clean disk
	qemu-system-i386 -fda $(SRCDIR)/floppy.img -boot a

debug: clean disk
	qemu-system-i386 -fda $(SRCDIR)/floppy.img -boot a -s &
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(SRCDIR)/kernel/kernel.elf"

disk: all
	$(IMAGEFS) c $(SRCDIR)/floppy.img 2880
	$(IMAGEFS) w $(SRCDIR)/floppy.img $(SRCDIR)/boot/stage1.bin
	$(PRSFS) $(SRCDIR)/floppy.img $(SRCDIR)/boot/stage2.bin $(SRCDIR)/kernel/kernel.bin

cdrom: disk
	cd .. && mkisofs -pad -b floppy.img -R -o ./$(PROJECT_NAME)/boot32-barebones.iso ./$(PROJECT_NAME)

clean:
	rm -f $(TARGETS)
	cd $(SRCDIR)/boot && make clean
	cd $(SRCDIR)/kernel && make clean
	cd $(SRCDIR)/imagefs && make clean
	cd $(SRCDIR)/prsfs && make clean

distclean: clean
	rm -f floppy.img $(CDROM_IMG) *.bak *.log
	cd $(SRCDIR)/boot && make distclean
	cd $(SRCDIR)/kernel && make distclean
	cd $(SRCDIR)/imagefs && make distclean
	cd $(SRCDIR)/prsfs && make distclean

dist: distclean
	cd .. && tar -cv --exclude=.git $(SRCDIR)/$(PROJECT_NAME) \
| xz -9 > $(PROJECT_NAME)-$(PROJECT_VERSION).tar.xz
