#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *encode(FILE *stream);
char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char *argv[])
{
	if (argc == 1)
		return 1;

	FILE *f = fopen(argv[1], "r");
	char *encoded = encode(f);
	printf("%s\n", encoded);

	return 0;
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

		nextByte = fgetc(stream);
		if (nextByte == EOF)
			continue;
		// get first 2 bits and make them bits 5 and 6
		bitMask = (bitMask & 0x3) << 4;
		bitMask |= nextByte >> 4;
		encoded[idx++] = base64[bitMask];

		// get bits 0-3 of nextByte and make them bits 2-5
		bitMask = (nextByte & 0xf) << 2;
		nextByte = fgetc(stream);
		if (nextByte == EOF)
			continue;
		// get last 2 bits of nextByte and make then the first 2
		bitMask &= nextByte >> 6;
		encoded[idx++] = base64[bitMask];
		// get the first 6 bits of nextByte
		bitMask = nextByte & 0x3f;
		encoded[idx++] = base64[bitMask];
	}

	return encoded;
}
