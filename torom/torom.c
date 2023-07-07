#include <stdio.h>

#include "torom.h"

#define todigit(c)      ((c) - '0')

int strtonum(char *str)
{
	int ret = 0;
	while (*str) {
		ret *= 10;
		ret += todigit(*str++);
	}
	return ret;
}
