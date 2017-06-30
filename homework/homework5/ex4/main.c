//
// Created by liu on 17-6-24.
//

#include "rsa.h"

int main()
{
    rsa_key key = rsa_generate(RSA_128);
    rsa_key_print(key, stdout);

    uint8_t m[] = {0x01, 0x23, 0x45, 0x67,
                   0x89, 0xab, 0xcd, 0xef,
                   0xfe, 0xdc, 0xba, 0x98,
                   0x76, 0x54, 0x32, 0x10};

    size_t m_size = sizeof(m) / sizeof(uint8_t);
    rsa_pair c = rsa_encrypt(m, m_size, key.n, key.n_size, key.e, key.e_size);
    rsa_pair mm = rsa_decrypt(c.bytes, c.size, key.n, key.n_size, key.d, key.d_size);

    printf("\nplaintext  : ");
    rsa_bytes_print(m, m_size, stdout);
    printf("\nciphertext : ");
    rsa_bytes_print(c.bytes, c.size, stdout);
    printf("\ndecrypted  : ");
    rsa_bytes_print(mm.bytes, mm.size, stdout);
    printf("\n");

    rsa_key_free(key);
    rsa_pair_free(c);
    rsa_pair_free(mm);

    return 0;
}