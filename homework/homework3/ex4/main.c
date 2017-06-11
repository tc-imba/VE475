//
// Created by liu on 17-6-12.
//

#include <stdio.h>
#include "aes.h"

int main()
{
    uint8_t a[16] = {
            0xEA, 0x04, 0x65, 0x85,
            0x83, 0x45, 0x5D, 0x96,
            0x5C, 0x33, 0x98, 0xB0,
            0xF0, 0x2D, 0xAD, 0xC5
    };
    uint8_t text[16] = {
            0x01, 0x89, 0xfe, 0x76,
            0x23, 0xab, 0xdc, 0x54,
            0x45, 0xcd, 0xba, 0x32,
            0x67, 0xef, 0x98, 0x10
    };
    uint8_t key[16] = {
            0x0f, 0x47, 0x0c, 0xaf,
            0x15, 0xd9, 0xb7, 0x7f,
            0x71, 0xe8, 0xad, 0x67,
            0xc9, 0x59, 0xd6, 0x98
    };
    uint8_t *bytes = aes_encode(text, key);
    //uint8_t **round_key = generate_round_key(a);
    sub_bytes(a);
    aes_print(a);
    shift_rows(a);
    aes_print(a);
    mix_columns(a);
    aes_print(a);
    mix_columns_inv(a);
    aes_print(a);
    //aes_print(bytes);

    bytes = aes_decode(bytes, key);
    //aes_print(bytes);


    /*for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            printf("%02x\t", round_key[i][j]);
            if (j % 4 == 3) printf("\n");
        }
        printf("\n");
    }*/
    return 0;
}