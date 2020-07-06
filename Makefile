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
	cd $(SRCDIR)/boot && $(MAKE)
	cd $(SRCDIR)/kernel && $(MAKE)
	cd $(SRCDIR)/imagefs && $(MAKE)
	cd $(SRCDIR)/prsfs && $(MAKE)

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
	cd $(SRCDIR)/boot && $(MAKE) clean
	cd $(SRCDIR)/kernel && $(MAKE) clean
	cd $(SRCDIR)/imagefs && $(MAKE) clean
	cd $(SRCDIR)/prsfs && $(MAKE) clean

distclean: clean
	rm -f floppy.img $(CDROM_IMG) *.bak *.log
	cd $(SRCDIR)/boot && $(MAKE) distclean
	cd $(SRCDIR)/kernel && $(MAKE) distclean
	cd $(SRCDIR)/imagefs && $(MAKE) distclean
	cd $(SRCDIR)/prsfs && $(MAKE) distclean

dist: distclean
	cd .. && tar -cv --exclude=.git $(SRCDIR)/$(PROJECT_NAME) \
| xz -9 > $(PROJECT_NAME)-$(PROJECT_VERSION).tar.xz
