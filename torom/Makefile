SRC = torom.c handleArgs.c
MAIN = main.c
TEST = tests.c
OBJ = $(SRC:.c=.o)
MAIN_OBJ = $(MAIN:.c=.o)
TEST_OBJ = $(TEST:.c=.o)
BINDIR = /usr/local/bin
CC = cc
EXE = torom
STRIP = strip
CFLAGS = -pedantic -Wall -O2


.PHONY: all test help strip install uninstall clean

default: all

all: $(EXE)

test: $(OBJ) $(TEST_OBJ)
	+$(CC) $(CFLAGS) -o $@ $(OBJ) $(TEST_OBJ)

help:
	@echo "To compile, type:"
	@echo ""
	@echo "make [target]"
	@echo ""
	@echo "Where target is one of the following:"
	@echo ""
	@echo "all:              > Compile for release"
	@echo "test:             > Compile for testing"
	@echo "help:             > Print this message"
	@echo "strip:            > Strip $(EXE)"
	@echo "install:          > Strip and install $(EXE)"
	@echo "uninstall:        > Uninstall $(EXE)"
	@echo "clean:            > Clean up"
	@echo ""
	@echo "If no target is given, it will use \"all\""

strip:
	$(STRIP) $(EXE)

install: strip
	-mkdir -p -m 755 $(BINDIR)
	-cp $(EXE) $(BINDIR)

uninstall:
	rm -f $(BINDIR)/$(EXE)

clean:
	rm -f $(EXE) test $(OBJ) $(TEST_OBJ) $(MAIN_OBJ)

$(EXE): $(OBJ) $(MAIN_OBJ)
	+$(CC) $(CFLAGS) -o $@ $(OBJ) $(MAIN_OBJ)

$(OBJ) $(MAIN_OBJ) $(TEST_OBJ): torom.h

$(TEST_OBJ): sunit.h tests.h
