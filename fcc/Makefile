BINDIR = /usr/local/bin
MANDIR = /usr/local/man
CC = cc
STRIP = strip
CFLAGS = -pedantic -Wall -O2


.PHONY: all help strip install clean

default: all

all: fcc

help:
	@echo "To compile, type:"
	@echo ""
	@echo "make [target]"
	@echo ""
	@echo "Where target is one of the following:"
	@echo ""
	@echo "all:              > Compile and link all source files"
	@echo "help:             > Print this message"
	@echo "strip:            > Strip the executable"
	@echo "[An object file]  > Recompiles and re-links the object file if needed"
	@echo "install:          > Strip and install the executable"
	@echo "uninstall:        > Uninstall the executable"
	@echo "clean:            > Clean up"
	@echo ""
	@echo "If no target is given, it will use \"all\""

strip:
	$(STRIP) fcc

install: strip
	-mkdir -p -m 755 $(BINDIR)
	-cp fcc $(BINDIR)
	-mkdir -p $(MANDIR)/man1
	-chmod 644 $(MANDIR)/man1/fcc.1

uninstall:
	rm -f $(BINDIR)/fcc

clean:
	rm -f fcc

# 'fcc.c' needs to be a dependency or make will always say fcc is up to date
fcc: fcc.c
	+$(CC) $(CFLAGS) -o $@ fcc.c
