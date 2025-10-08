#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "GIFT64.h"

uint64_t string_to_uint64(const char* str) {
    uint64_t result = 0;
    size_t len = strlen(str);
    size_t copy_len = (len > 8) ? 8 : len; // Only take first 8 characters for 64 bits
    
    for (size_t i = 0; i < copy_len; i++) {
        result |= ((uint64_t)str[i] << (8 * i));
    }
    return result;
}

void uint64_to_string(uint64_t value, char* buffer) {
    for (int i = 0; i < 8; i++) {
        buffer[i] = (char)(value >> (8 * i));
    }
    buffer[8] = '\0';
}

int main() {
    //Test Vector 1
    // uint64_t plaintext1 = 0x0;
    // uint16_t key1[8] = {0000, 0000, 0000, 0000, 0000, 0000, 0000, 0000 };
    // printf("Plaintext: %"SCNx64 "\n", plaintext1);
    // printf("masterkey: ");
    // int k;
    // for(k = 0; k < 8; k++) {
    //     printf("%x " ,key1[k]);
    // }
    // printf("\n");
    

    //Test Vector 2
    // uint64_t plaintext2 = 0xfedcba9876543210;
    // uint16_t key2[8] = {0xfedc, 0xba98, 0x7654, 0x3210, 0xfedc, 0xba98, 0x7654, 0x3210 };
    // printf("Plaintext: %"SCNx64 "\n", plaintext2);
    // printf("masterkey: ");  
    // int k;
    // for(k = 0; k < 8; k++) {
    //     printf("%x " ,key2[k]);
    // }
    // printf("\n");

    //Test Vector 3
    const char* hello_world = "Hello World";
    uint64_t plaintext3 = string_to_uint64(hello_world);
    uint16_t key3[8] = {0xbd91, 0x731e, 0xb6bc, 0x2713, 0xa1f9, 0xf6ff, 0xc750, 0x44e7};
    printf("Plaintext: %"SCNx64 "\n", plaintext3);
    printf("masterkey: ");  
    int k;
    for(k = 0; k < 8; k++) {
        printf("%x " ,key3[k]);
    }
    printf("\n");

    uint64_t EncryptedValue = GIFT64_Encryption(plaintext3,key3);
    printf("CipherText: %"SCNx64 "\n", EncryptedValue);
    uint64_t DecryptedValue = GIFT64_Decryption(EncryptedValue,key3);
    printf("DecryptedValue: %"SCNx64 "\n", DecryptedValue);

    char decrypted_str[9];
    uint64_to_string(DecryptedValue, decrypted_str);
    printf("Decrypted string: %s\n", decrypted_str);
    /******* Testing Encryption and Decryption *******/
    
    /*****Print Binary: ********/
    // uint64_t constant1 = 1;
    // uint64_t v = (constant1<<63);
    // convert64bittoBinary(v);
    /**************** Testing SubCells ********************/
    // uint64_t subvalue = SubCells(plaintext);
    // printf("SubCells: %"SCNu64 "\n", subvalue);
    // uint64_t invsubvalue = InvSubCells(subvalue);
    // printf("InvSubCells: %"SCNu64 "\n", invsubvalue);
    
    /********** Create InvPermBit ***********/
    // uint8_t InvPTable[64];
    // int j;
    // for(j = 0; j < 64; j++) {
    //     InvPTable[PermTable[j]] = j;
    // }
    // for(j = 0; j < 64; j++) {
    //     printf("%"SCNu8 ", " ,InvPTable[j]);
    // }
    // printf("\n");

    /**************** Testing PermBits ********************/
    // uint64_t subvalue = PermBits(plaintext);
    // printf("PermBits: %"SCNu64 "\n", subvalue);
    // printf("PermBits in binary: ");
    // convert64bittoBinary(subvalue);
    // uint64_t invsubvalue = InvPermBits(subvalue);
    // printf("InvPermBits: %"SCNu64 "\n", invsubvalue);
    // printf("InvPermBits in binary: ");
    // convert64bittoBinary(invsubvalue);
    /********** Constant Schedule ********/ 
    /* int i;
    uint64_t constant = 0x01;
    printf("0x%x, ", constant);
    for(i = 2; i < 49; i++) {
        uint64_t c0 = constant & 0x01;
        uint64_t c1 = (constant>>1) & 0x01;
        uint64_t c2 = (constant>>2) & 0x01;
        uint64_t c3 = (constant>>3) & 0x01;
        uint64_t c4 = (constant>>4) & 0x01;
        uint64_t c5 = (constant>>5) & 0x01;
        uint64_t temp = c5 ^c4 ^0x01; 
        constant = (c4 << 5) ^ (c3 << 4) ^ (c2 << 3) ^ (c1 << 2) ^ (c0 << 1) ^ temp;
        printf("0x%x, ", constant);
    } */
    /*********** Test Key Schedule *************/
    // uint16_t ** W;
    // W = KeySchedule(key);
    // uint16_t * key2 = W[0];
    // int i;
    // for(i=0; i < 8; i++) {
    //     printf("%"SCNx16 ", ", key2[i]);
    // }
    // printf("\n");
    /************* Testing AddKey *************/
    // uint64_t value = AddRoundKey(plaintext, key, 11);
    // printf("AddKey: %"SCNu64 "\n", value);
    // uint64_t invvalue = AddRoundKey(value, key, 11);
    // printf("InvAddKey: %"SCNu64 "\n", invvalue);

    
    return 0;
}



