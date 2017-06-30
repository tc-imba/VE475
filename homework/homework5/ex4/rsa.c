//
// Created by liu on 17-6-24.
//

#include "rsa.h"
#include <gmp.h>
#include <time.h>
#include <memory.h>

rsa_key rsa_generate(RSA_SECURITY security)
{
    rsa_key key;

    // Init the size
    if (security < 0)security = RSA_80;
    else if (security >= sizeof(RSA_SIZE) / sizeof(size_t)) security = RSA_256;
    key.security = security;
    size_t len = RSA_SIZE[security];
    size_t p_len = len / 2 - len / 128;
    size_t q_len = len / 2 + len / 128;

    // Init the random machine
    gmp_randstate_t randstate;
    gmp_randinit_mt(randstate);
    gmp_randseed_ui(randstate, (unsigned) time(NULL));

    // Init some integers
    mpz_t p, q, n, pb, qb;
    mpz_inits(p, q, n, pb, qb, NULL);
    mpz_ui_pow_ui(pb, 2, p_len - 1);
    mpz_ui_pow_ui(qb, 2, q_len - 1);

    // Generate p, q
    while (1)
    {
        mpz_urandomb(p, randstate, p_len - 1);
        mpz_add(p, p, pb);
        if (mpz_even_p(p)) mpz_sub_ui(p, p, 1);
        if (mpz_probab_prime_p(p, 15)) break;
    }
    while (1)
    {
        mpz_urandomb(q, randstate, q_len - 1);
        mpz_add(q, q, qb);
        if (mpz_even_p(q)) mpz_sub_ui(q, q, 1);
        if (mpz_probab_prime_p(q, 15)) break;
    }

    // Calculate n and save p, q, n
    mpz_mul(n, p, q);
    size_t count;
    key.p = mpz_export(NULL, &count, 1, 1, 0, 0, p);
    key.p_size = count;
    key.q = mpz_export(NULL, &count, 1, 1, 0, 0, q);
    key.q_size = count;
    key.n = mpz_export(NULL, &count, 1, 1, 0, 0, n);
    key.n_size = count;

    // Init some integers
    mpz_t phi, e, d, gcd;
    mpz_inits(phi, e, d, gcd, NULL);

    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);

    // Calculate and save e, d
    while (1)
    {
        mpz_urandomb(e, randstate, len - 2);
        if (mpz_even_p(e)) mpz_add_ui(e, e, 1);
        mpz_gcd(gcd, e, phi);
        if (mpz_cmp_ui(gcd, 1) == 0)break;
    }
    mpz_invert(d, e, phi);
    key.e = mpz_export(NULL, &count, 1, 1, 0, 0, e);
    key.e_size = count;
    key.d = mpz_export(NULL, &count, 1, 1, 0, 0, d);
    key.d_size = count;

    // Free the memory
    mpz_clears(p, q, n, pb, qb, phi, e, d, gcd, NULL);
    gmp_randclear(randstate);

    return key;
}

void rsa_key_free(rsa_key key)
{
    free(key.p);
    free(key.q);
    free(key.n);
    free(key.d);
    free(key.e);
}

void rsa_pair_free(rsa_pair pair)
{
    free(pair.bytes);
}


void rsa_bytes_print(uint8_t *bytes, size_t size, FILE *stream)
{
    if (size == 0)return;
    fprintf(stream, "%X", bytes[0]);
    rsa_bytes_print(bytes + 1, size - 1, stream);
}

void rsa_key_print(rsa_key key, FILE *stream)
{
    fprintf(stream, "n: ");
    rsa_bytes_print(key.n, key.n_size, stream);
    fprintf(stream, "\n");

    fprintf(stream, "d: ");
    rsa_bytes_print(key.d, key.d_size, stream);
    fprintf(stream, "\n");

    fprintf(stream, "e: ");
    rsa_bytes_print(key.e, key.e_size, stream);
    fprintf(stream, "\n");
}

rsa_pair rsa_encrypt(uint8_t *m_bytes, size_t m_size, uint8_t *n_bytes, size_t n_size, uint8_t *e_bytes, size_t e_size)
{
    rsa_pair result;
    mpz_t m, n, e, c;
    mpz_inits(m, n, e, c, NULL);
    mpz_import(m, m_size, 1, 1, 0, 0, m_bytes);
    mpz_import(n, n_size, 1, 1, 0, 0, n_bytes);
    mpz_import(e, e_size, 1, 1, 0, 0, e_bytes);
    mpz_powm(c, m, e, n);
    result.bytes = mpz_export(NULL, &result.size, 1, 1, 0, 0, c);
    mpz_clears(m ,n, e, c, NULL);
    return result;
}

rsa_pair rsa_decrypt(uint8_t *c_bytes, size_t c_size, uint8_t *n_bytes, size_t n_size, uint8_t *d_bytes, size_t d_size)
{
    rsa_pair result;
    mpz_t c, n, d, m;
    mpz_inits(c, n, d, m, NULL);
    mpz_import(c, c_size, 1, 1, 0, 0, c_bytes);
    mpz_import(n, n_size, 1, 1, 0, 0, n_bytes);
    mpz_import(d, d_size, 1, 1, 0, 0, d_bytes);
    mpz_powm(m, c, d, n);
    result.bytes = mpz_export(NULL, &result.size, 1, 1, 0, 0, m);
    mpz_clears(c, n, d, m, NULL);
    return result;
}