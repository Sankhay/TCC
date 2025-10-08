#define CHACHA20_IMPLEMENTATION
#include "ChaCha20.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

void string_to_hex_array(const char* str, uint8_t* output, size_t* length) {
	*length = strlen(str);

	for (size_t i = 0; i < *length; i++) {
		output[i] = (uint8_t)str[i];
	}
}

void hex_array_to_string(const uint8_t* data, size_t length, char* output) {
	for (size_t i = 0; i < length; i++) {
		output[i] = (char)data[i];
	}
	output[length] = '\0';
}

void print_hex_array(const uint8_t* data, size_t length) {
    printf("uint8_t data[] = {\n");
    for (size_t i = 0; i < length; i++) {
        printf("0x%02x", data[i]);
        if (i < length - 1) {
            printf(", ");
        }
        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n};\n");
}

// Usage

int main()
{
	key256_t key = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	};

	nonce96_t nonce = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a,
		0x00, 0x00, 0x00, 0x00,
	};

	uint32_t count = 0x00000001;

	const char* text = "Hello World";
	uint8_t data[50];
	size_t data_length;

	string_to_hex_array(text, data, &data_length);

	printf("%s\n", data);
	printf("%s\n", data);

	ChaCha20_Ctx ctx;
	ChaCha20_init(&ctx, key, nonce, count);
	ChaCha20_xor(&ctx, data, sizeof(data));

	printf("%s\n", data);

	ChaCha20_init(&ctx, key, nonce, count);  // Reset to initial state
	ChaCha20_xor(&ctx, data, sizeof(data));

	// The array 'data' is now encrypted (or decrypted if it
	// was already encrypted)

	printf("%s\n", data);

	/*char recovered_text[50];

	hex_array_to_string(data, data_length, recovered_text);

	printf("%s", recovered_text);*/
}

