#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	if (argc == 1)
		return 0;

	int messageLen;
	char* message;

	for (int word = 1; word < argc; word++) {
		messageLen = strlen(argv[word]);
		message = malloc(messageLen + 1); // null char

		//for some reason, strcat() broke, so I had to write my own version
		{
			char *dest = message;
			char *src = argv[word];
			while (*dest++ = *src++);
		}
		message[messageLen] = '\0';

		while(messageLen--) {
			printf("%s\n", message);
			message[messageLen] = '\0';
		}
		if (argc - word != 1)
			printf("\n");

		free(message);
	}

	return 0;
}
