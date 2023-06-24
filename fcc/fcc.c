/* lc - print the number of letters in files
 *
 * This program comes without ANY license or warranty, including any implied
 * warranty. You are free to copy, modify and redistribute it as you see fit.
 */

#include <stdio.h>
#include <string.h>

#define DEFAULT_COLUMN_WIDTH 12

const char space[] = " ";

int main(int argc, char *argv[])
{
	int count = 0;

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
	argv--;

	// TODO: add custom args for each file
	while (*++argv) {
		FILE *file;
		int currLetterCount = 0;
		int spacing;
		int fileNameWidth;
		int columnWidth;
		int numWidth;

		file = fopen(*argv, "r");
		if (file == 0) {
			fprintf(stderr, "Could not open file \"%s\"\n", *argv);
			continue;
		}

		while (fgetc(file) != EOF)
			currLetterCount++;
		count += currLetterCount;

		/*  fileNameWidth  DEFAULT_COLUMN_WIDTH
		 * |---|          |--------------------|
		 * file:          <chars>               Total: <chars>
		 * |-------------|
		 * columnWidth
		 *
		 * columWidth = MAX(DEFAULT_COLUMN_WIDTH, fileNameWidth rounded
		 * up to the nearest 4)
		 */

		fileNameWidth = strlen(*argv) + 1;
		if (fileNameWidth >= DEFAULT_COLUMN_WIDTH)
			columnWidth = ((fileNameWidth >> 2) + 1) << 2;
		else
			columnWidth = DEFAULT_COLUMN_WIDTH;

		if (DEFAULT_COLUMN_WIDTH * 2 > fileNameWidth)
			spacing = (columnWidth - fileNameWidth);
		else
			spacing = 1;

		// + 4 because of the tab after the number
		numWidth = -(DEFAULT_COLUMN_WIDTH * 2 - columnWidth - 4);
		if (numWidth > 0)
			numWidth = 0;

		printf("%s:%*s%*d\tTotal: %d\n", *argv, spacing, space,
				numWidth, currLetterCount, count);
	}

	printf("\nTotal count: %d\n", count);

	return 0;
}
