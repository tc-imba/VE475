//
// Created by liu on 17-6-24.
//

#ifndef VE475_RSA_H
#define VE475_RSA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef enum
{
    RSA_80,
    RSA_112,
    RSA_128,
    RSA_192,
    RSA_256
} RSA_SECURITY;

static const size_t RSA_SIZE[] = {1024, 2048, 3072, 7680, 15360};

typedef struct rsa_key_t
{
    RSA_SECURITY security;
    uint8_t *p, *q, *n, *d, *e;
    size_t p_size, q_size, n_size, d_size, e_size;
} rsa_key;

typedef struct rsa_pair_t
{
    uint8_t *bytes;
    size_t size;
} rsa_pair;

/**
 * Free the memory used in rsa_key
 * @param key
 */
void rsa_key_free(rsa_key key);

/**
 * Free the memory used in rsa_pair
 * @param pair
 */
void rsa_pair_free(rsa_pair pair);

/**
 * Print the data of given size to the stream
 * @param bytes
 * @param size
 * @param stream
 */
void rsa_bytes_print(uint8_t *bytes, size_t size, FILE *stream);

/**
 * Print n, d, e of the rsa_key to the stream
 * @param key
 * @param stream
 */
void rsa_key_print(rsa_key key, FILE *stream);

/**
 * Generate a rsa_key according to the security
 * @param security
 * @return
 */
rsa_key rsa_generate(RSA_SECURITY security);

/**
 * Encrypt a plaintext with n and e
 * @param m_bytes plaintext
 * @param m_size  size of plaintext
 * @param n_bytes n=p*q
 * @param n_size  size of n
 * @param e_bytes e chosen in generation
 * @param e_size  size of e
 * @return
 */
rsa_pair rsa_encrypt(uint8_t *m_bytes, size_t m_size, uint8_t *n_bytes, size_t n_size, uint8_t *e_bytes, size_t e_size);

/**
 * Decrypt a ciphertext with n and d
 * @param c_bytes ciphertext
 * @param c_size  size of ciphertext
 * @param n_bytes n=p*q
 * @param n_size  size of n
 * @param d_bytes d chosen in generation
 * @param d_size  size of d
 * @return
 */
rsa_pair rsa_decrypt(uint8_t *c_bytes, size_t c_size, uint8_t *n_bytes, size_t n_size, uint8_t *d_bytes, size_t d_size);


#endif //VE475_RSA_H
