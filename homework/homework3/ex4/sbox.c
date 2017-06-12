//
// Created by liu on 17-6-13.
//

#include <stdint.h>
#include <stdio.h>

const uint8_t transform_matrix[8] = {
        0xF8, 0x7C, 0x3E, 0x1F, 0x8F, 0xC7, 0xE3, 0xF1
};

uint8_t xor_map[0x100] = {};

#define AES_MULTI_TWO_MACRO(a) (uint8_t)(((a) >= 0x80) ? (((a << 1)) ^ 0x1B) : ((a) << 1))

// Multiplication of a and b in GF(2^8)
uint8_t multi(uint8_t a, uint8_t b)
{
    if (b == 1)return a;
    if (b == 2)return AES_MULTI_TWO_MACRO(a);
    if (b & 1)return a ^ AES_MULTI_TWO_MACRO(multi(a, b >> 1));
    return AES_MULTI_TWO_MACRO(multi(a, b >> 1));
}

// Calculate the invert of byte in GF(2^8)
uint8_t invert(uint8_t byte)
{
    if (byte == 0)return byte;
    for (int i = 1; i < 0x100; i++)
    {
        if (multi(byte, i) == 1)return (uint8_t) i;
    }
}

// Transform with the matrix
uint8_t transform(uint8_t byte)
{
    uint8_t result = 0;
    for (int i = 0; i < 8; i++)
    {
        result |= (xor_map[byte & transform_matrix[i]] << (7 - i));
    }
    result ^= 0x63;
    return result;
}


int main()
{
    // Init the xor_map
    for (int i = 0; i < 0x100; i++)
    {
        uint8_t a = (uint8_t) i, b = 0;
        while (a > 0)
        {
            b ^= (a & 1);
            a >>= 1;
        }
        xor_map[i] = b;
    }

    // Print the S-box
    uint8_t sbox[0x100] = {};
    uint8_t sbox_inv[0x100] = {};
    for (int i = 0; i < 0x100; i++)
    {
        sbox[i] = transform(invert(i));
        sbox_inv[sbox[i]] = (uint8_t) i;
        printf("%02X\t", sbox[i]);
        if (i % 16 == 15)printf("\n");
    }

    printf("\n");

    // Print the inverse S-box
    for (int i = 0; i < 0x100; i++)
    {
        printf("%02X\t", sbox_inv[i]);
        if (i % 16 == 15)printf("\n");
    }

    return 0;
}