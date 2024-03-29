#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define todigit(c) ((c) - '0')

char *encode(FILE *stream);
char *decode(FILE *stream);
// is only called once, so it will exit the program on its own
void displayHelp(void);
int toint(char *str);

static struct {
	unsigned long int encode : 1;
	// not implemented
	unsigned long int ignoreGarbage : 1;
	// wrap after `wrap` columns; not implemented
	int wrap;
} flags;

static char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char *argv[])
{
	if (argc == 1) {
		displayHelp();
		return 0;
	}

	int i = 1;
	flags.encode = 1;
	flags.ignoreGarbage = 0;
	flags.wrap = 79;

	for (; i < argc && argv[i][0] == '-'; i++) {
		switch (argv[i][1]) {
			case 'd':
				flags.encode = 0;
				break;
			case 'i':
				flags.ignoreGarbage = 1;
				break;
			case 'w':
				if (++i < argc)
					flags.wrap = toint(argv[i]);
				break;
			case 'h':
				displayHelp();
				// technically redundant buts helps readability
				break;
			default:
				fprintf(stderr, "Unrecognised argument "
						"\"%s\"\n", argv[i]);
				break;
		}
	}

	if (i == argc) {
		fprintf(stderr, "Last argument must be a file\n");
		return 1;
	}

	FILE *f = fopen(argv[i], "r");
	if (f == NULL) {
		fprintf(stderr, "Cannot open file for reading\n");
		return 1;
	}

	char *output;
	if (flags.encode)
		output = encode(f);
	else
		output = decode(f);

	fclose(f);
	printf("%s\n", output);

	return 0;
}

void displayHelp(void)
{
	printf("base64cpy\n"
	       "base64 encode/decode a file to standard output.\n"
	       "\n"
	       "Usage: base64cpy [OPTION] ... [FILE]\n"
	       "\n"
	       "Options:\n"
	       "    -d		decode data\n"
	       "    -i		ignore garbage when decoding "
			"(non-alphanumeric)\n"
	       "    -w		wrap encoded data after n characters (default "
			"%d)\n"
	       "    -h		display this message and exit\n", flags.wrap);
	exit(0);
}

char *encode(FILE *stream)
{
	char nextByte = 0;
	int bitMask = 0;
	int idx = 0;
	// 1 for the null char at the end
	char *encoded = malloc(idx + 1);
	// until EOF
	while (nextByte != EOF) {
		/* from each triplet of bytes, these bits are fetched:
		 * 0000 0000 0000 0000 0000 0000
		 * `-----`
		 *        `-----`
		 *                `-----`
		 *                       `-----`
		 * and repeat
		 */

		encoded = realloc(encoded, (idx + 4) * sizeof(char));

		nextByte = fgetc(stream);
		if (nextByte == EOF)
			continue;
		// get the first 6 bits of nextByte, which is also all but the
		// last 2 bits
		bitMask = nextByte >> 2;
		encoded[idx++] = base64[bitMask];

		// get first 2 bits, make them the last, then pad them
		// out with 0's
		bitMask = (nextByte & 0x3) << 4;
		nextByte = fgetc(stream);
		if (nextByte == EOF)
			continue;
		// make the last 4 bits the first
		bitMask |= nextByte >> 4;
		encoded[idx++] = base64[bitMask];

		// get bits 0-3 of nextByte and make them bits 2-5
		bitMask = (nextByte & 0xf) << 2;
		nextByte = fgetc(stream);
		if (nextByte == EOF)
			continue;
		// get last 2 bits of nextByte and make then the first 2
		bitMask |= nextByte >> 6;
		encoded[idx++] = base64[bitMask];

		// get the first 6 bits of nextByte
		bitMask = nextByte & 0x3f;
		encoded[idx++] = base64[bitMask];
	}

	// idx mod 4, which checks how much padding is needed.
	switch (idx & 0x3) {
		// no padding needed
		case 0:
			break;
		// first 2 bits need to be accounted for
		case 1:
			encoded[idx++] = base64[bitMask];
			encoded[idx++] = '=';
			encoded[idx++] = '=';
			break;
		case 2:
			// bitMask is already set. No need to pad it out with
			// 0's because it's already padded.
			encoded[idx++] = base64[bitMask];
			encoded[idx++] = '=';
			break;
		case 3:
		default:
			fprintf(stderr, "how the hell did you get here");
	}
	encoded[idx] = '\0';

	return encoded;
}

char *decode(FILE *stream)
{
	// implement
	return "Decoding not implemented yet";
}

int toint(char *str)
{
	int ret = 0;
	while (*str)
		ret = ret * 10 + todigit(*str++);
	return ret;
}
