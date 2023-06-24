#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define u8 uint8_t

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
	u8 nextByte = 0;
	int bitMask = 0;
	int length = 0;
	char *encoded = malloc(0);
	// until EOF
	while (1)
	{
		/* from each triplet of bytes, these bits are fetched:
		 * 0000 0000 0000 0000 0000 0000
		 * `-----`
		 *        `-----`
		 *                `-----`
		 *                       `-----`
		 * and repeat
		 */

		length += 4;
		encoded = realloc(encoded, length * sizeof(char));

		nextByte = fgetc(stream);
		bitMask = nextByte >> 2;
		encoded[length - 4] = base64[bitMask];
		nextByte = fgetc(stream);
		bitMask <<= 4;
		bitMask &= nextByte >> 4;
		encoded[length - 3] = base64[bitMask];
		bitMask = (nextByte & 0xf) << 2;
		nextByte = fgetc(stream);
		bitMask &= nextByte >> 6;
		encoded[length - 2] = base64[bitMask];
		bitMask = nextByte & 0x3f;
		encoded[length - 1] = base64[bitMask];
	}

	return encoded;
}
