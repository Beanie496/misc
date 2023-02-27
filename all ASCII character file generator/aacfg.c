#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void generate(char cmd[], char path[])
{
	char* finalCmd;
	int sizeOfCmd  = strlen(cmd) + 1; // including the null char
	int sizeOfPath;


	if (path != 0) {
		sizeOfPath = strlen(path) + 1;
		if (path[sizeOfPath - 2] != '/') { // last non-null char
			path = realloc(path, ++sizeOfPath);
			path[sizeOfPath - 2] = '/';
			path[sizeOfPath - 1] = '\0';
		}
	} else {
		sizeOfPath = 4; // "./\0"
		path = malloc(sizeOfPath);
		path = "./\\";
	}

	// "command\0path/\0'char' " is same size as "command path/char\0"
	finalCmd = malloc(sizeOfCmd + sizeOfPath + 1);
	strcpy(finalCmd, cmd);
	finalCmd[sizeOfCmd - 1] = ' ';
	strcpy(finalCmd + sizeOfCmd, path);
	// leaves a single char, 1 before the null char, to be changed
	finalCmd[sizeOfCmd + sizeOfPath] = '\0';

	char i = 0;
	do {
		finalCmd[sizeOfCmd + sizeOfPath - 1] = i;
		printf("command = %s; i = %c or %d\n", finalCmd, i, i);
		system(finalCmd);
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

	if (flags & (1 << 2))
		generate("rm -f", pathPtr);
	else
		generate("touch", pathPtr);

	if (pathPtr != 0)
		free(pathPtr);


	return 0;
}
