//
// Created by liu on 17-6-12.
//

#include "aes.h"

void aes_print(uint8_t bytes[0x10])
{
    for (int i = 0; i < 16; i++)
    {
        printf("%02x\t", bytes[i]);
        //if (i % 4 == 3) printf("\n");
    }
    printf("\n");
}

static void swap(uint8_t *a, uint8_t *b)
{
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}

void sub_bytes(uint8_t bytes[0x10])
{
    bytes[0x0] = AES_SBOX[bytes[0x0]];
    bytes[0x1] = AES_SBOX[bytes[0x1]];
    bytes[0x2] = AES_SBOX[bytes[0x2]];
    bytes[0x3] = AES_SBOX[bytes[0x3]];
    bytes[0x4] = AES_SBOX[bytes[0x4]];
    bytes[0x5] = AES_SBOX[bytes[0x5]];
    bytes[0x6] = AES_SBOX[bytes[0x6]];
    bytes[0x7] = AES_SBOX[bytes[0x7]];
    bytes[0x8] = AES_SBOX[bytes[0x8]];
    bytes[0x9] = AES_SBOX[bytes[0x9]];
    bytes[0xA] = AES_SBOX[bytes[0xA]];
    bytes[0xB] = AES_SBOX[bytes[0xB]];
    bytes[0xC] = AES_SBOX[bytes[0xC]];
    bytes[0xD] = AES_SBOX[bytes[0xD]];
    bytes[0xE] = AES_SBOX[bytes[0xE]];
    bytes[0xF] = AES_SBOX[bytes[0xF]];
}

void sub_bytes_inv(uint8_t bytes[0x10])
{
    bytes[0x0] = AES_SBOX_INV[bytes[0x0]];
    bytes[0x1] = AES_SBOX_INV[bytes[0x1]];
    bytes[0x2] = AES_SBOX_INV[bytes[0x2]];
    bytes[0x3] = AES_SBOX_INV[bytes[0x3]];
    bytes[0x4] = AES_SBOX_INV[bytes[0x4]];
    bytes[0x5] = AES_SBOX_INV[bytes[0x5]];
    bytes[0x6] = AES_SBOX_INV[bytes[0x6]];
    bytes[0x7] = AES_SBOX_INV[bytes[0x7]];
    bytes[0x8] = AES_SBOX_INV[bytes[0x8]];
    bytes[0x9] = AES_SBOX_INV[bytes[0x9]];
    bytes[0xA] = AES_SBOX_INV[bytes[0xA]];
    bytes[0xB] = AES_SBOX_INV[bytes[0xB]];
    bytes[0xC] = AES_SBOX_INV[bytes[0xC]];
    bytes[0xD] = AES_SBOX_INV[bytes[0xD]];
    bytes[0xE] = AES_SBOX_INV[bytes[0xE]];
    bytes[0xF] = AES_SBOX_INV[bytes[0xF]];
}

void shift_rows(uint8_t bytes[0x10])
{
    uint8_t temp = bytes[0x4];
    bytes[0x4] = bytes[0x5];
    bytes[0x5] = bytes[0x6];
    bytes[0x6] = bytes[0x7];
    bytes[0x7] = temp;
    swap(&bytes[0x8], &bytes[0xA]);
    swap(&bytes[0x9], &bytes[0xB]);
    temp = bytes[0xF];
    bytes[0xF] = bytes[0xE];
    bytes[0xE] = bytes[0xD];
    bytes[0xD] = bytes[0xC];
    bytes[0xC] = temp;
}

void shift_rows_inv(uint8_t bytes[0x10])
{
    uint8_t temp = bytes[0x7];
    bytes[0x7] = bytes[0x6];
    bytes[0x6] = bytes[0x5];
    bytes[0x5] = bytes[0x4];
    bytes[0x4] = temp;
    swap(&bytes[0x8], &bytes[0xA]);
    swap(&bytes[0x9], &bytes[0xB]);
    temp = bytes[0xC];
    bytes[0xC] = bytes[0xD];
    bytes[0xD] = bytes[0xE];
    bytes[0xE] = bytes[0xF];
    bytes[0xF] = temp;
}

#define AES_MULTI_TWO_MACRO(a) (AES_MULTI_TWO[(a)])
#define AES_MULTI_THREE_MACRO(a) (AES_MULTI_TWO_MACRO(a) ^ (a))
#define AES_MULTI_FOUR_MACRO(a) (AES_MULTI_TWO_MACRO(AES_MULTI_TWO_MACRO(a)))
#define AES_MULTI_FIVE_MACRO(a) (AES_MULTI_FOUR_MACRO(a) ^ (a))
#define AES_MULTI_SIX_MACRO(a) (AES_MULTI_TWO_MACRO(a) ^ AES_MULTI_FOUR_MACRO(a))
#define AES_MULTI_EIGHT_MACRO(a) (AES_MULTI_TWO_MACRO(AES_MULTI_TWO_MACRO(AES_MULTI_TWO_MACRO(a))))

#define AES_MIX_COLUMN_MACRO(offset) \
temp[0] = bytes[0x0 + (offset)]; \
temp[1] = bytes[0x4 + (offset)]; \
temp[2] = bytes[0x8 + (offset)]; \
temp[3] = bytes[0xC + (offset)]; \
temp[4] = temp[0] ^ temp[1] ^ temp[2] ^ temp[3]; \
bytes[0x0 + (offset)] = temp[0] ^ temp[4] ^ AES_MULTI_TWO_MACRO(temp[0] ^ temp[1]); \
bytes[0x4 + (offset)] = temp[1] ^ temp[4] ^ AES_MULTI_TWO_MACRO(temp[1] ^ temp[2]); \
bytes[0x8 + (offset)] = temp[2] ^ temp[4] ^ AES_MULTI_TWO_MACRO(temp[2] ^ temp[3]); \
bytes[0xC + (offset)] = temp[3] ^ temp[4] ^ AES_MULTI_TWO_MACRO(temp[3] ^ temp[0]); \

#define AES_MIX_COLUMN_INV_MACRO(offset) \
temp[0] = bytes[0x0 + (offset)]; \
temp[1] = bytes[0x4 + (offset)]; \
temp[2] = bytes[0x8 + (offset)]; \
temp[3] = bytes[0xC + (offset)]; \
temp[4] = temp[0] ^ temp[1] ^ temp[2] ^ temp[3]; \
bytes[0x0 + (offset)] = AES_MULTI_EIGHT_MACRO(temp[4]) ^ AES_MULTI_SIX_MACRO(temp[0]) ^ AES_MULTI_THREE_MACRO(temp[1]) ^ AES_MULTI_FIVE_MACRO(temp[2]) ^ temp[3]; \
bytes[0x4 + (offset)] = AES_MULTI_EIGHT_MACRO(temp[4]) ^ AES_MULTI_SIX_MACRO(temp[1]) ^ AES_MULTI_THREE_MACRO(temp[2]) ^ AES_MULTI_FIVE_MACRO(temp[3]) ^ temp[0]; \
bytes[0x8 + (offset)] = AES_MULTI_EIGHT_MACRO(temp[4]) ^ AES_MULTI_SIX_MACRO(temp[2]) ^ AES_MULTI_THREE_MACRO(temp[3]) ^ AES_MULTI_FIVE_MACRO(temp[0]) ^ temp[1]; \
bytes[0xC + (offset)] = AES_MULTI_EIGHT_MACRO(temp[4]) ^ AES_MULTI_SIX_MACRO(temp[3]) ^ AES_MULTI_THREE_MACRO(temp[0]) ^ AES_MULTI_FIVE_MACRO(temp[1]) ^ temp[2]; \


void mix_columns(uint8_t bytes[0x10])
{
    uint8_t temp[5];
    AES_MIX_COLUMN_MACRO(0)
    AES_MIX_COLUMN_MACRO(1)
    AES_MIX_COLUMN_MACRO(2)
    AES_MIX_COLUMN_MACRO(3)
}

void mix_columns_inv(uint8_t bytes[0x10])
{
    uint8_t temp[5];
    AES_MIX_COLUMN_INV_MACRO(0)
    AES_MIX_COLUMN_INV_MACRO(1)
    AES_MIX_COLUMN_INV_MACRO(2)
    AES_MIX_COLUMN_INV_MACRO(3)
}

#undef AES_MIX_COLUMN_MACRO
#undef AES_MULTI_TWO_MACRO
#undef AES_MULTI_THREE_MACRO
#undef AES_MULTI_FOUR_MACRO
#undef AES_MULTI_FIVE_MACRO
#undef AES_MULTI_SIX_MACRO
#undef AES_MULTI_EIGHT_MACRO

void add_round_key(uint8_t bytes[0x10], uint8_t key[0x10])
{
    bytes[0x0] ^= key[0x0];
    bytes[0x1] ^= key[0x1];
    bytes[0x2] ^= key[0x2];
    bytes[0x3] ^= key[0x3];
    bytes[0x4] ^= key[0x4];
    bytes[0x5] ^= key[0x5];
    bytes[0x6] ^= key[0x6];
    bytes[0x7] ^= key[0x7];
    bytes[0x8] ^= key[0x8];
    bytes[0x9] ^= key[0x9];
    bytes[0xA] ^= key[0xA];
    bytes[0xB] ^= key[0xB];
    bytes[0xC] ^= key[0xC];
    bytes[0xD] ^= key[0xD];
    bytes[0xE] ^= key[0xE];
    bytes[0xF] ^= key[0xF];
}

uint8_t *transform_bytes(const uint8_t bytes[0x10])
{
    uint8_t *bytes2 = malloc(0x10 * sizeof(uint8_t));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            bytes2[i * 4 + j] = bytes[j * 4 + i];
    return bytes2;
}

uint8_t **generate_round_key(const uint8_t key[0x10])
{
    uint8_t **round_key = malloc(11 * sizeof(uint8_t *));
    round_key[0] = transform_bytes(key);
    for (int i = 1; i < 11; i++) round_key[i] = malloc(0x10 * sizeof(uint8_t));
    for (int i = 1; i < 11; i++)
    {
        round_key[i][0x0] = round_key[i - 1][0x0] ^ (AES_SBOX[round_key[i - 1][0x7]] ^ AES_RCON[i]);
        round_key[i][0x4] = round_key[i - 1][0x4] ^ (AES_SBOX[round_key[i - 1][0xB]] ^ ((uint8_t) (0)));
        round_key[i][0x8] = round_key[i - 1][0x8] ^ (AES_SBOX[round_key[i - 1][0xF]] ^ ((uint8_t) (0)));
        round_key[i][0xC] = round_key[i - 1][0xC] ^ (AES_SBOX[round_key[i - 1][0x3]] ^ ((uint8_t) (0)));
        for (int j = 0; j < 0x10; j++)
        {
            if (j % 4 != 0)round_key[i][j] = round_key[i][j - 1] ^ round_key[i - 1][j];
        }
    }
    return round_key;
}

void free_round_key(uint8_t **round_key)
{
    for (int i = 0; i < 11; i++)
    {
        free(round_key[i]);
    }
    free(round_key);
}

uint8_t *aes_encode(const uint8_t text[0x10], const uint8_t key[0x10])
{
    uint8_t **round_key = generate_round_key(key);
    uint8_t *bytes = transform_bytes(text);
    add_round_key(bytes, round_key[0]);
    for (int i = 1; i <= 9; i++)
    {
        sub_bytes(bytes);
        shift_rows(bytes);
        mix_columns(bytes);
        add_round_key(bytes, round_key[i]);
    }
    sub_bytes(bytes);
    shift_rows(bytes);
    add_round_key(bytes, round_key[10]);
    free_round_key(round_key);
    uint8_t *bytes2 = transform_bytes(bytes);
    free(bytes);
    return bytes2;
}

uint8_t *aes_decode(const uint8_t text[0x10], const uint8_t key[0x10])
{
    uint8_t **round_key = generate_round_key(key);
    uint8_t *bytes = transform_bytes(text);
    add_round_key(bytes, round_key[10]);
    for (int i = 1; i <= 9; i++)
    {
        shift_rows_inv(bytes);
        sub_bytes_inv(bytes);
        add_round_key(bytes, round_key[10 - i]);
        mix_columns_inv(bytes);
    }
    shift_rows_inv(bytes);
    sub_bytes_inv(bytes);
    add_round_key(bytes, round_key[0]);
    free_round_key(round_key);
    uint8_t *bytes2 = transform_bytes(bytes);
    free(bytes);
    return bytes2;
}

