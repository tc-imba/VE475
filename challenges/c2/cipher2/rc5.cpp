//
// Created by liu on 17-7-12.
//

#include "rc5.h"

void encrypt(uint32_t &a, uint32_t &b, const uint32_t s[], const uint8_t &n)
{
    a ^= b;
    a = ROTATE_LEFT(a, b);
    a += s[n];
    a &= RC5_MASK;
    b ^= a;
    b = ROTATE_LEFT(b, a);
    b += s[n + 1];
    b &= RC5_MASK;
}

void decrypt(uint32_t &a, uint32_t &b, const uint32_t s[], const uint8_t &n)
{
    b -= s[n + 1];
    b &= RC5_MASK;
    b = ROTATE_RIGHT(b, a);
    b ^= a;
    a -= s[n];
    a &= RC5_MASK;
    a = ROTATE_RIGHT(a, b);
    a ^= b;
}

uint32_t combine(const uint8_t byte[4])
{
    uint32_t a;
    a = byte[3];
    a <<= 8;
    a += byte[2];
    a <<= 8;
    a += byte[1];
    a <<= 8;
    a += byte[0];
    return a;
}

void split(uint32_t n, uint8_t byte[4])
{
    byte[0] = n;
    n >>= 8;
    byte[1] = n;
    n >>= 8;
    byte[2] = n;
    n >>= 8;
    byte[3] = n;
}


uint8_t *rc5_encode(const uint8_t text[8], const uint32_t key[34])
{
    uint32_t a, b;
    a = combine(text) + key[0];
    b = combine(text + 4) + key[1];

    encrypt(a, b, key, 2);
    encrypt(a, b, key, 4);
    encrypt(a, b, key, 6);
    encrypt(a, b, key, 8);
    encrypt(a, b, key, 10);
    encrypt(a, b, key, 12);
    encrypt(a, b, key, 14);
    encrypt(a, b, key, 16);
    encrypt(a, b, key, 18);
    encrypt(a, b, key, 20);
    encrypt(a, b, key, 22);
    encrypt(a, b, key, 24);
    encrypt(a, b, key, 26);
    encrypt(a, b, key, 28);
    encrypt(a, b, key, 30);
    encrypt(a, b, key, 32);

    auto result = (uint8_t *) malloc(sizeof(uint8_t) * 8);

    split(a, result);
    split(b, result + 4);

    return result;
}


uint8_t *rc5_decode(const uint8_t text[8], const uint32_t key[34])
{
    uint32_t a, b;
    a = combine(text);
    b = combine(text + 4);

    decrypt(a, b, key, 32);
    decrypt(a, b, key, 30);
    decrypt(a, b, key, 28);
    decrypt(a, b, key, 26);
    decrypt(a, b, key, 24);
    decrypt(a, b, key, 22);
    decrypt(a, b, key, 20);
    decrypt(a, b, key, 18);
    decrypt(a, b, key, 16);
    decrypt(a, b, key, 14);
    decrypt(a, b, key, 12);
    decrypt(a, b, key, 10);
    decrypt(a, b, key, 8);
    decrypt(a, b, key, 6);
    decrypt(a, b, key, 4);
    decrypt(a, b, key, 2);

    a -= key[0];
    b -= key[1];

    auto result = (uint8_t *) malloc(sizeof(uint8_t) * 8);

    split(a, result);
    split(b, result + 4);

    return result;
}


void f1(const uint8_t *c, uint32_t &l1, uint32_t &l2, uint32_t &n)
{
    c += n;
    l1 = l2 = 0;
    switch (n)
    {
        case 8:
            l2 = ((uint32_t) (*(--(c)))) << 24L;
        case 7:
            l2 |= ((uint32_t) (*(--(c)))) << 16L;
        case 6:
            l2 |= ((uint32_t) (*(--(c)))) << 8L;
        case 5:
            l2 |= ((uint32_t) (*(--(c))));
        case 4:
            l1 = ((uint32_t) (*(--(c)))) << 24L;
        case 3:
            l1 |= ((uint32_t) (*(--(c)))) << 16L;
        case 2:
            l1 |= ((uint32_t) (*(--(c)))) << 8L;
        case 1:
            l1 |= ((uint32_t) (*(--(c))));
        default:
            break;
    }
}

void f2(const uint8_t *c, uint32_t &l)
{
    l = ((uint32_t) (*((c)++)));
    l |= ((uint32_t) (*((c)++))) << 8L;
    l |= ((uint32_t) (*((c)++))) << 16L;
    l |= ((uint32_t) (*((c)++))) << 24L;
}

uint32_t *rc5_generate_key(const uint8_t *data, const uint32_t &len)
{
    uint32_t arr[64], l, l_, A, B, k;
    uint32_t i, j, i_, j_, m;
    const uint32_t length = (len + 3) / 4, size = 34;

    auto result = (uint32_t *) malloc(34 * sizeof(uint32_t));
    j = 0;
    for (i = 0; i <= (len - 8); i += 8)
    {
        f2(data, l);
        arr[j++] = l;
        f2(data, l);
        arr[j++] = l;
    }

    if (i_ = len - i)
    {
        k = len & 0x07;
        f1(data, l, l_, k);
        arr[j + 0] = l;
        arr[j + 1] = l_;
    }

    result[0] = RC5_P;
    for (i = 1; i < size; i++)
        result[i] = (result[i - 1] + RC5_Q) & RC5_MASK;

    j = (size > length) ? size : length;
    j *= 3;
    i_ = j_ = 0;
    A = B = 0;
    for (i = 0; i < j; i++)
    {
        k = (result[i_] + A + B) & RC5_MASK;
        A = result[i_] = ROTATE_LEFT(k, 3);
        m = (int) (A + B);
        k = (arr[j_] + A + B) & RC5_MASK;
        B = arr[j_] = ROTATE_LEFT(k, m);
        if (++i_ >= size)i_ = 0;
        if (++j_ >= length)j_ = 0;
    }
    return result;
}
