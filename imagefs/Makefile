# =============================================================
# Simple Makefile for imagefs
# Created by Philip R. Simonson
# =============================================================
CC=gcc
CFLAGS=-std=c89 -Wall -Wextra -Werror -Wno-unused-parameter
LDFLAGS=

TARGET=imagefs
SOURCE=$(wildcard *.c)
OBJECT=$(SOURCE:%.c=%.c.o)

BACKUPS=$(shell find . -iname "*.bak")

.PHONY: all clean distclean
all: $(TARGET)

%.c.o: %.c
	@echo CC $(CFLAGS) -c -o $@ $<
	@$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECT)
	@echo CCLD $(CFLAGS) $(LDFLAGS) -o $@ $^
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJECT) $(TARGET)

distclean:
ifneq ($(BACKUPS),)
	rm -f $(BACKUPS)
endif
