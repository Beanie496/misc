BINDIR = /usr/local/bin
CC = cc
STRIP = strip
EXE = base64cpy
CFLAGS = -pedantic -Wall -O2


.PHONY: all help strip install clean

default: all

all: base64cpy

help:
	@echo "To compile, type:"
	@echo ""
	@echo "make [target]"
	@echo ""
	@echo "Where target is one of the following:"
	@echo ""
	@echo "all:              > Compile"
	@echo "help:             > Print this message"
	@echo "strip:            > Strip base64cpy"
	@echo "install:          > Strip and install base64cpy"
	@echo "uninstall:        > Uninstall base64cpy"
	@echo "clean:            > Clean up"
	@echo ""
	@echo "If no target is given, it will use \"all\""

strip:
	$(STRIP) base64cpy

install: strip
	-mkdir -p -m 755 $(BINDIR)
	-cp base64cpy $(BINDIR)

uninstall:
	rm -f $(BINDIR)/base64cpy

clean:
	rm -f base64cpy

base64cpy: base64cpy.c
	+$(CC) $(CFLAGS) -o base64cpy base64cpy.c
