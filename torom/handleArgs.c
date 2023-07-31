#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "torom.h"

Args args;

void handleArgs(int argc, char *argv[])
{
	if (argc == 1) {
		fprintf(stderr, "Must provide at least one argument\n");
		exit(1);
	}
	args.firstArg = argv[1];
}
