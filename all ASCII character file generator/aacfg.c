#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void generate(char path[])
{
	FILE *file;

	char *name;
	int lengthOfPath = sizeof(path);
	int lengthOfName;
	if (path[sizeOfPath - 1] == '/') {
		// name + null char
		lengthOfName = (lengthOfPath + 1) * sizeof(char);
		name = malloc(lengthOfName + 1 * sizeof(char));
		name[lengthOfName] = '\0';
	} else {
		// slash + name + null char
		lengthOfName = (lengthOfPath + 2) * sizeof(char);
		name = malloc(lengthOfName + 1 * sizeof(char));
		name[lengthOfName] = '\0';
		name[lengthOfName - 2] = '/';
	}


	char i = 0;
	do {
		name[lengthOfName - 1] = i;
		file = fopen(name, "w");
		fclose(file);
		printf("created file \"%c\" (%d)\n", finalCmd, i, i);
		i++;
	} while (i != 0);

	free(finalCmd);
}


int main(int argc, char* argv[]) {
	char flags = 0; // bits 0-7: wants help, has given path, is deleting files
	char* pathPtr = 0;

	for (int arg = 1; arg < argc; arg++) {
		if (argv[arg][0] == '-') {
			if (argv[arg][1] == 'h')
				flags |= 1 << 0;

			if (argv[arg][1] == 'p') {
				if (argc - arg != 1) {
					if (flags & (1 << 1))
						free(pathPtr);
					pathPtr = malloc(sizeof(argv[arg + 1]));
					strcpy(pathPtr, argv[arg + 1]);
				} else {
					flags |= 1 << 1;
				}
			}

			if (argv[arg][1] == 'c')
				flags &= ~(1 << 2);

			if (argv[arg][1] == 'd')
				flags |= 1 << 2;
		}
	}

	if (flags & (1 << 0)) {
		printf("Usage: \"aacfc [options]\"\n"
		       "\n"
			   "Options:\n"
			   "  -h/--help       prints this message\n"
		       "  -p/--path=PATH  gives a path to directory to spawn files\n"
			   "                  in; otherwise, spawn in current directory\n"
		       "  -c/--create     creates all the files (default)\n"
		       "  -d/--delete     deletes all the files\n");
		return 0;
	}

	if (flags & (1 << 1) && pathPtr == 0)
		printf("Path mentioned but not given. "
		       "Defaulting to current directory.\n");

	generate(pathPtr);

	free(pathPtr);


	return 0;
}
