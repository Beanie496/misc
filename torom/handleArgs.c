#include <stddef.h>

#include "torom.h"

Args args;

void handleArgs(int argc, char *argv[])
{
	if (argc == 1)
		args.firstArg = NULL;
	else
		args.firstArg = argv[1];
}
