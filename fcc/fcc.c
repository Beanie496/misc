/* lc - print the number of letters in files
 *
 * This program comes without ANY license or warranty, including any implied
 * warranty. You are free to copy, modify and redistribute it as you see fit.
 */

#include <stdio.h>
#include <string.h>

#define DEFAULT_COLUMN_WIDTH 12

void prettyPrint(char *fileName, int fileNameWidth, int fileTotal, int total);

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

		file = fopen(*argv, "r");
		if (file == 0) {
			fprintf(stderr, "Could not open file \"%s\"\n", *argv);
			continue;
		}

		while (fgetc(file) != EOF)
			currLetterCount++;
		fclose(file);
		count += currLetterCount;

		prettyPrint(*argv, strlen(*argv) + 1, currLetterCount, count);
	}

	printf("\nTotal count: %d\n", count);

	return 0;
}

void prettyPrint(char *fileName, int fileNameWidth, int fileTotal, int total)
{
	static const char space[] = " ";
	int columnWidth;
	int numWidth;
	int spacing;

	/*  fileNameWidth  DEFAULT_COLUMN_WIDTH
	 * |---|          |--------------------|
	 * file:          <chars>               Total: <chars>
	 * |-------------|
	 * columnWidth
	 *
	 * columWidth = MAX(DEFAULT_COLUMN_WIDTH, fileNameWidth rounded
	 * up to the nearest 4)
	 */

	if (fileNameWidth >= DEFAULT_COLUMN_WIDTH)
		// leave a space between the colon and number
		columnWidth = fileNameWidth + 1;
	else
		columnWidth = DEFAULT_COLUMN_WIDTH;

	// if fileNameWidth > DEFAULT_COLUMN_WIDTH, spacing == 1
	spacing = (columnWidth - fileNameWidth);

	// - 4 because of the tab after the number
	numWidth = -(DEFAULT_COLUMN_WIDTH * 2 - columnWidth - 4);
	if (numWidth > 0)
		numWidth = 0;

	printf("%s:%*s%*d\tTotal: %d\n", fileName, spacing, space,
			numWidth, fileTotal, total);
}
