//
// Created by liu on 17-6-12.
//

#include "aes.h"

int main()
{
    uint8_t text[16] = {
            0x01, 0x23, 0x45, 0x67,
            0x89, 0xab, 0xcd, 0xef,
            0xfe, 0xdc, 0xba, 0x98,
            0x76, 0x54, 0x32, 0x10
    };
    uint8_t key[16] = {
            0x0f, 0x47, 0x0c, 0xaf,
            0x15, 0xd9, 0xb7, 0x7f,
            0x71, 0xe8, 0xad, 0x67,
            0xc9, 0x59, 0xd6, 0x98
    };

    aes_print(text);
    aes_print(key);

    uint8_t *bytes = aes_encode(text, key);
    aes_print(bytes);

    uint8_t *bytes2 = aes_decode(bytes, key);
    aes_print(bytes2);

    free(bytes);
    free(bytes2);

    return 0;
}