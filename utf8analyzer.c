#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
int codepoint_size(const char str[])
{
	unsigned char c = (unsigned char) str[0];
	if ((c & 0b10000000) == 0b00000000) {return 1;}
	else if ((c & 0b11100000) == 0b11000000) {return 2;}
	else if ((c & 0b11110000) == 0b11100000) {return 3;}
	else if ((c & 0b11111000) == 0b11110000) {return 4;}

	return -1;
}

int bytes_per_codepoint(const char str[])
{
	int index = 0;
	int length = 0;

	printf("Bytes per codepoints: ");
	while (str[index] != '\0')
	{
		int size = codepoint_size(&str[index]);

		if (size == -1)
		{
			return -1;
		}


		printf(" %d ", size);
		
		index +=size;
		length++;
	}

	printf("\n");
	return length;
}

void print_first_6_codepoints(const char str[])
{
	int index = 0;
	int copy = 0;
	int count = 0;

	char result[2048];

	while (str[index] != '\0' && count < 6)
	{
		int size = codepoint_size(&str[index]);
		if (size == -1)
		{
			return;
		}

		for (int i = 0; i < size; i++)
		{
			result[copy++] = str[index + i];
		}

		index += size;
		count++;

	}

	result[copy] = '\0';

	printf("First 6 codepoints: %s\n", result);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"<UTF-8 encoded string>\"\n", argv[0]);
        return 1;
    }

    bytes_per_codepoint(argv[1]);
    print_first_6_codepoints(argv[1]);
    return 0;
    // implement the UTF-8 analyzer here
}
