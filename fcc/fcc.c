/* lc - print the number of letters in files
 *
 * This program comes without ANY license or warranty, including any implied
 * warranty. You are free to copy, modify and redistribute it as you see fit.
 */

#include <stdio.h>


int main(int argc, char *argv[])
{
	int count = 0;
	FILE *file;

	// TODO: handle command-line args
	while (*(++argv)[0] == '-')
		while (*++*argv)
			switch (**argv) {
				case 'a':
					break;
				case 'c':
					break;
				case 'f':
					break;
				case 'h':
					break;
				case 'l':
					break;
				case 'n':
					break;
				case 's':
					break;
				case 'v':
					break;
				default:
					break;
			}

	// TODO: add custom args for each file
	argv--;
	while (*++argv) {
		int currLetterCount = 0;
		file = fopen(*argv, "r");
		if (file == 0) {
			fprintf(stderr, "Could not open file \"%s\"\n", *argv);
			continue;
		}
		while (fgetc(file) != EOF) {
			currLetterCount++;
		}
		count += currLetterCount;
		printf("Count for this file: %d.\t\t Count total: %d\n",
				currLetterCount, count);
	}

	printf("Total count: %d\n", count);

	return 0;
}
