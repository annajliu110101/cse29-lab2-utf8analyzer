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


// 8
void is_all_animal_emoji(char str[]){
	// int c_point = 0;
	int i = 0;

	while (str[i] != 0) {
		char c = str[i];
		int num = 0;
		if ((c & 0b10000000) == 0b00000000) {
			num = c;
			i += 1;
		}
		else if ((c & 0b11100000) == 0b11000000) {
			num = ((c & 0b00011111) << 6) | (str[i + 1] & 0b00111111);
			i += 2;
		}
		else if ((c & 0b11110000) == 0b11100000) {
			num = ((c & 0b00001111) << 12) | ((str[i + 1] & 0b00111111) << 6) | (str[i + 2] & 0b00111111);
			i += 3;
		}
		else if ((c & 0b11111000) == 0b11110000) {
			num = ((c & 0b00000111) << 18) | ((str[i + 1] & 0b00111111) << 12) | ((str[i + 2] & 0b00111111) << 6) | (str[i + 3] & 0b00111111);
			i += 4;
		}
		
		if (!((num >= 0x1F400 && num <= 0x1F43F) || (num >= 0x1F980 && num <= 0x1F9AE))){
			printf("Problem 8: Not all animal emojis in the input string!\n");
			return;
		}	
	}
	printf("Problem 8: All animal emojis in input string!\n");

} 

// 9
void code_point_with_value_one_higher_at_i3(char str[]){
        int c_point = 0;
        int i = 0;

        // go to start
        while (c_point < 2) {
                char c = str[i];
                if ((c & 0b10000000) == 0b00000000){i += 1;}
                else if ((c & 0b11100000) == 0b11000000){i += 2;}
                else if ((c & 0b11110000) == 0b11100000){i += 3;}
                else if ((c & 0b11111000) == 0b11110000){i += 4;}
                c_point++;
        }

        char c = str[i];
	uint32_t codeP = 0;
	if ((c & 0b10000000) == 0b00000000){
                codeP = c;
        }
        else if ((c & 0b11100000) == 0b11000000){
                codeP = ((c & 0b00011111) << 6) | (str[i + 1] & 0b00111111);
        }
        else if ((c & 0b11110000) == 0b11100000){
                codeP = ((c & 0b00001111) << 12) | ((str[i + 1] & 0b00111111) << 6) | (str[i + 2] & 0b00111111);
        }
        else if ((c & 0b11111000) == 0b11110000){
                codeP = ((c & 0b00000111) << 18) | ((str[i + 1] & 0b00111111) << 12) | ((str[i + 2] & 0b00111111) << 6) | (str[i + 3] & 0b00111111);
        }

	codeP++;

	char dest[5] = {0, 0, 0, 0, 0};
	if (codeP <= 0x7F){
                dest[0] = codeP & 0x7F;
        }
        else if (codeP <= 0b11111111111){
                dest[0] = 0xC0 | ((codeP >> 6) & 0b00011111);
                dest[1] = 0x80 | (codeP & 0b00111111);
        }
        else if (codeP <= 0b1111111111111111) {
                dest[0] = 0xE0 | ((codeP >> 12) & 0b00001111);
                dest[1] = 0x80 | ((codeP >> 6 ) & 0b00111111);
                dest[2] = 0x80 | (codeP & 0b00111111);
        }
        else if (codeP <= 0b111111111111111111111) {
                dest[0] = 0xF0 | ((codeP >> 18) & 0b00000111);
                dest[1] = 0x80 | ((codeP >> 12) & 0b00111111);
                dest[2] = 0x80 | ((codeP >> 6 ) & 0b00111111);
                dest[3] = 0x80 | (codeP & 0b00111111);
        }
	
	printf("Problem 9: %s\n", dest);
	

}



int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"<UTF-8 encoded string>\"\n", argv[0]);
        return 1;
    }

    bytes_per_codepoint(argv[1]);
    print_first_6_codepoints(argv[1]);
    
    // implement the UTF-8 analyzer here

    
    // problem 8
	is_all_animal_emoji(argv[1]);
    // problem 9
	code_point_with_value_one_higher_at_i3(argv[1]);


    return 0;
}
