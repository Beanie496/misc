/* lc - print the number of letters in files
 *
 * This program comes without ANY license or warranty, including any implied
 * warranty. You are free to copy, modify and redistribute it as you see fit.
 */

#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int count = 0;
	int longestFile = 0;
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

	for (char **arg = argv--; *arg; arg++) {
		int len;
		if ((len = strlen(*arg)) > longestFile)
			longestFile = len;
	}

	// TODO: add custom args for each file
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
		// TODO: fix the colons
		printf("Total: %-12d%*s: %d\n", count, -longestFile, *argv,
				currLetterCount);
	}

	printf("\nTotal count: %d\n", count);

	return 0;
}
