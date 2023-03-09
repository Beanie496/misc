#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned int wantsHelp : 1;
	unsigned int hasGivenPath : 1;
	unsigned int isCreatingFiles : 1;
} Flags;


void generate(char path[], int isCreatingFiles)
{
	FILE *file;

	char *name;
	int lengthOfName;
	int lengthOfPath;

	if (path == NULL) {
		lengthOfName = 1;
		name = malloc(lengthOfName * sizeof(char));
	} else {
		lengthOfPath = strlen(path);

		if (path[lengthOfPath - 1] == '/') {
			lengthOfName = lengthOfPath + 1;
			name = malloc((lengthOfName + 1) * sizeof(char));
		} else {
			// slash + name + null char
			lengthOfName = lengthOfPath + 2;
			name = malloc((lengthOfName + 1) * sizeof(char));
			name[lengthOfName - 2] = '/';
		}
	}
	name[lengthOfName] = '\0';


	char i = 1;
	do {
		name[lengthOfName - 1] = i;
		if (isCreatingFiles) {
			fprintf(stderr, "Attempting to create file \"%c\" (%d)", i, i);
			// TODO: creating file "." creates segfault. Fix this.
			file = fopen(name, "w+");
			fclose(file);
			fprintf(stderr, " [success]\n");
		} else {
			fprintf(stderr, "Attempting to delete file \"%c\" (%d)", i, i);
			remove(name);
			fprintf(stderr, " [success]\n");
		}
		i++;
	} while (i != 0);

	free(name);
}


int main(int argc, char* argv[]) {
	Flags flags = { 0, 0, 0 };
	char *parameter = NULL;

	while (--argc > 0) {
		if (argv[argc][0] != '-') {
			parameter = malloc(strlen(argv[argc]) * sizeof(char *));
			strcpy(parameter, argv[argc]);
			continue;
		}

		switch(argv[argc][1]) {
			case 'h':
				flags.wantsHelp = 1;
				break;

			case 'p':
				flags.hasGivenPath = 1;
				break;

			case 'c':
				flags.isCreatingFiles = 1;
				break;

			case 'd':
				flags.isCreatingFiles = 0;
				break;

			default:
				printf("Unknown argument \"%s\"\n", argv[argc]);
				return 1;
		}
	}

	if (flags.wantsHelp) {
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

	if (flags.hasGivenPath && parameter == NULL)
		printf("Path mentioned but not given. "
		       "Defaulting to current directory.\n");

	generate(parameter, flags.isCreatingFiles);

	free(parameter);


	return 0;
}
