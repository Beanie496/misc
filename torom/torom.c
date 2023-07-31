#include <stdio.h>

#include "torom.h"

#define todigit(c)      ((c) - '0')

char *torom(int num)
{
	switch (num) {
		case 1000:
			return "M";
		case 500:
			return "D";
		case 100:
			return "C";
		case 50:
			return "L";
		case 10:
			return "X";
		case 5:
			return "V";
		case 1:
			return "I";
		default:
			return "";
	}
}

int strtonum(char *str)
{
	int ret = 0;
	while (*str) {
		ret *= 10;
		ret += todigit(*str++);
	}
	return ret;
}
