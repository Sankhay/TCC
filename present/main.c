#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "present.c"

void print_hex(const char *label, const unsigned char *data, size_t len) {
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main(){
    char plaintext[] = "HelloWorHelloWor/n";
    char key[] = "MySecret98";
    
    printf("Original plaintext: '%s'\n", plaintext);
    printf("Plaintext length: %zu\n", strlen(plaintext));
    
    char *ciphertext = encrypt(plaintext, key);
    
    // Print ciphertext in hex (it might contain non-printable characters)
    print_hex("Ciphertext (hex)", (unsigned char*)ciphertext, strlen(plaintext));
    
    printf("The ciphertext as string: ");
    puts(ciphertext); // This might not show properly
    
    char *decrypted = decrypt(ciphertext, key);
    
    printf("Decrypted text: '%s'\n", decrypted);
    printf("Decrypted length: %zu\n", strlen(decrypted));
    
    // Compare original vs decrypted
    if (strcmp(plaintext, decrypted) == 0) {
        printf("SUCCESS: Encryption/decryption works correctly!\n");
    } else {
        printf("ERROR: Decrypted text doesn't match original!\n");
    }
    
    free(ciphertext);
    free(decrypted);
    return 0;
}