/* 'owoify' - a program to turn regular text into an owo-ified version of it.
 * What it does to the text is:
 * - makes the whole message lowercase
 * - replaces any instances of 'r' or 'l' with 'w'
 * - replaces any instances of 'n' followed by a vowel with "ny"
 * - repeats any words that don't start with 'w', are at least 5 characters long, have a vowel and end with 'y'
 *   - repeated words have all the characters preceeding the vowel replaced with 'w'
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define DEFAULT_CHANCE 10
#define MAX_WORD_LEN 1000
#define isvowel(c) (((c) == 'a' || (c) == 'e' || (c) == 'i' || (c) == 'o' || (c) == 'u') ? 1 : 0)

struct wordFlags {
	unsigned int startsWithW : 1;
	unsigned int hasVowel : 1;
	unsigned int endsInY : 1;
	unsigned int isAtLeast5CharsLong : 1;
};

void owoify(char input[], int percentage);


int main(int argc, char* argv[]) {
	int percentage = DEFAULT_CHANCE;
	int argLen = 0;
	int word = 1; // starting from the first option to parse throught the options better

	srand(time(0));

	if (argc == 1) {
		printf("usage: \"owoify [-h] [-s chance] {stwing}\". \"-h\" pwints mowe infowmation on the options :3\n");
		return 0;
	}

	if (!strcmp(argv[word], "-h")) {
		printf("owoptions:\n"
		       "  -h      pwints this message\n"
		       "  -s      gives a chance as a pewcentage for stuttew (defauwt is %d%%)~\n", DEFAULT_CHANCE);
		return 0;
	}
	
	if (!strcmp(argv[word], "-s")) {
		if (argc < 4) { // needs have percentage + string
			printf("invawid number of awguments~\n");
			return 0;
		}
		
		argLen = strlen(argv[++word]);

		if (argLen == 1) {
			printf("have to give a pewcentage :p\n");
			return 0;
		}

		if (argv[word][argLen - 1] != '%') {
			printf("not a pewcentage :3\n");
			return 0;
		}

		argv[word][argLen - 1] = '\0';
		percentage = atoi(argv[word]);
		if (percentage < 0 || percentage > 100) { // this is a little sloppy...but it's fine, for the most part
			printf("invawid pewcentage\n");
			return 0;
		}

		word++;
	}

	if (argv[word][0] == '-') {
		printf("Invawid option :c\n");
		return 0;
	}

	while (word < argc) { // this is why i used the 'word' variable
		owoify(argv[word++], percentage);
		printf(" ");
	}
	printf("\n");


	return 0;
}


void owoify(char input[], int percentage)
{
	int character = -1, lettersUntilVowel;
	int tempChar;
	char repeatStr[MAX_WORD_LEN];


	while (input[++character] != '\0')
		input[character] = tolower(input[character]);
	character = 0;

	while (input[character] != '\0') {
		struct wordFlags flags = { 0 };
		tempChar = 0;
		lettersUntilVowel = 0;


		while (!isalpha(input[character]) && input[character] != '\0')
			printf("%c", input[character++]);
		if (input[character] == '\0')
			return;

		if (input[character] == 'w')
			flags.startsWithW = 1;

		// chance for stutter
		if (rand() % 100 + 1 <= percentage) {
			if (input[character] == 'r' || input[character] == 'l')
				printf("w-");
			else	
				printf("%c-", input[character]);
		}

		while (isalpha(input[character]) || input[character] == '\'' || input[character] == '-') {

			if (isvowel(input[character])) {
				// "n<vowel>" -> "ny<vowel>"
				if (character > 0 && input[character - 1] == 'n')
					printf("%c", repeatStr[tempChar++] = 'y');
				flags.hasVowel = 1;

			} else if (!flags.hasVowel) {
				lettersUntilVowel++;
			}

			if (input[character] == 'r' || input[character] == 'l')
				input[character] = 'w';

			printf("%c", repeatStr[tempChar++] = input[character++]);
		}
		repeatStr[tempChar] = '\0';

		if (tempChar >= 5)
			flags.isAtLeast5CharsLong = 1;

		tempChar = character;
		// the character after the last would be a null character, so no chance of reading in a garbage value
		while (!isalpha(input[tempChar]))
			tempChar--;

		if (input[tempChar] == 'y')
			flags.endsInY = 1;

		 // are all 4 flags set?
		if (~flags.startsWithW & flags.hasVowel & flags.endsInY & flags.isAtLeast5CharsLong)
			// this has the effect of replacing all consonants before the vowel with 'w'
			printf(" w%s", repeatStr + lettersUntilVowel);
	}
}
