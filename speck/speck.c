#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ROR(x, r) ((x >> r) | (x << (64 - r)))
#define ROL(x, r) ((x << r) | (x >> (64 - r)))
#define R(x, y, k) (x = ROR(x, 8), x += y, x ^= k, y = ROL(y, 3), y ^= x)
#define RI(x, y, k) (y ^= x, y = ROR(y, 3), x ^= k, x -= y, x = ROL(x, 8))
#define ROUNDS 32

void encrypt(uint64_t ct[2],
             uint64_t const pt[2],            
             uint64_t const K[2])
{
   uint64_t y = pt[0], x = pt[1], b = K[0], a = K[1];

   R(x, y, b);
   for (int i = 0; i < ROUNDS - 1; i++) {
      R(a, b, i);
      R(x, y, b);
   }

   ct[0] = y;
   ct[1] = x;
}

void decrypt(uint64_t pt[2],
             uint64_t const ct[2],
             uint64_t const K[2])
{
   uint64_t y = ct[0], x = ct[1];
   uint64_t b = K[0], a = K[1];
   
   // Precompute all round keys (same as encryption)
   uint64_t round_keys[ROUNDS];
   round_keys[0] = b;
   
   for (int i = 0; i < ROUNDS - 1; i++) {
      R(a, b, i);
      round_keys[i + 1] = b;
   }
   
   // Apply inverse operations in reverse order
   for (int i = ROUNDS - 1; i > 0; i--) {
      RI(x, y, round_keys[i]);
   }
   RI(x, y, round_keys[0]);
   
   pt[0] = y;
   pt[1] = x;
}

// Helper function to print hex values
void print_hex(const char* label, uint64_t data[2]) {
    printf("%s: 0x%016lx%016lx\n", label, data[0], data[1]);
}

// Helper function to convert string to uint64_t array
void string_to_blocks(const char* str, uint64_t blocks[2]) {
    memcpy(blocks, str, 16);
}

// Helper function to print as string (if printable)
void print_string(const char* label, uint64_t data[2]) {
    printf("%s: ", label);
    unsigned char* bytes = (unsigned char*)data;
    for (int i = 0; i < 16; i++) {
        if (bytes[i] >= 32 && bytes[i] <= 126) {
            printf("%c", bytes[i]);
        } else {
            printf("\\x%02x", bytes[i]);
        }
    }
    printf("\n");
}

int main() {
    // Test case 1: Simple text
    uint64_t plaintext1[2] = {0x48656c6c6f20576f, 0x726c642121212121}; // "Hello World!!!!"
    uint64_t key1[2] = {0x0123456789abcdef, 0xfedcba9876543210};
    uint64_t ciphertext1[2], decrypted1[2];
    
    printf("=== Test Case 1: Simple Text ===\n");
    print_hex("Plaintext ", plaintext1);
    print_string("Plaintext ", plaintext1);
    print_hex("Key       ", key1);
    
    encrypt(ciphertext1, plaintext1, key1);
    print_hex("Ciphertext", ciphertext1);
    
    decrypt(decrypted1, ciphertext1, key1);
    print_hex("Decrypted ", decrypted1);
    print_string("Decrypted ", decrypted1);
    
    // Verify
    if (memcmp(plaintext1, decrypted1, 16) == 0) {
        printf("✓ Encryption/Decryption successful!\n");
    } else {
        printf("✗ Encryption/Decryption failed!\n");
    }
    
    printf("\n");
    
    // Test case 2: All zeros
    uint64_t plaintext2[2] = {0x0000000000000000, 0x0000000000000000};
    uint64_t key2[2] = {0xdeadbeefcafebabe, 0x1234567890abcdef};
    uint64_t ciphertext2[2], decrypted2[2];
    
    printf("=== Test Case 2: All Zeros ===\n");
    print_hex("Plaintext ", plaintext2);
    print_hex("Key       ", key2);
    
    encrypt(ciphertext2, plaintext2, key2);
    print_hex("Ciphertext", ciphertext2);
    
    decrypt(decrypted2, ciphertext2, key2);
    print_hex("Decrypted ", decrypted2);
    
    if (memcmp(plaintext2, decrypted2, 16) == 0) {
        printf("✓ Encryption/Decryption successful!\n");
    } else {
        printf("✗ Encryption/Decryption failed!\n");
    }
    
    printf("\n");
    
    // Test case 3: Maximum values
    uint64_t plaintext3[2] = {0xffffffffffffffff, 0xffffffffffffffff};
    uint64_t key3[2] = {0xffffffffffffffff, 0xffffffffffffffff};
    uint64_t ciphertext3[2], decrypted3[2];
    
    printf("=== Test Case 3: Maximum Values ===\n");
    print_hex("Plaintext ", plaintext3);
    print_hex("Key       ", key3);
    
    encrypt(ciphertext3, plaintext3, key3);
    print_hex("Ciphertext", ciphertext3);
    
    decrypt(decrypted3, ciphertext3, key3);
    print_hex("Decrypted ", decrypted3);
    
    if (memcmp(plaintext3, decrypted3, 16) == 0) {
        printf("✓ Encryption/Decryption successful!\n");
    } else {
        printf("✗ Encryption/Decryption failed!\n");
    }
    
    printf("\n");
    
    // Test case 4: Random values
    uint64_t plaintext4[2] = {0x1234567890abcdef, 0xfedcba0987654321};
    uint64_t key4[2] = {0x13579bdf2468ace0, 0x97531fdb86420eca};
    uint64_t ciphertext4[2], decrypted4[2];
    
    printf("=== Test Case 4: Random Values ===\n");
    print_hex("Plaintext ", plaintext4);
    print_hex("Key       ", key4);
    
    encrypt(ciphertext4, plaintext4, key4);
    print_hex("Ciphertext", ciphertext4);
    
    decrypt(decrypted4, ciphertext4, key4);
    print_hex("Decrypted ", decrypted4);
    
    if (memcmp(plaintext4, decrypted4, 16) == 0) {
        printf("✓ Encryption/Decryption successful!\n");
    } else {
        printf("✗ Encryption/Decryption failed!\n");
    }
    
    return 0;
}