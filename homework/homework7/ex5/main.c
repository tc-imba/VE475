//
// Created by liu on 17-7-14.
//

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <stdbool.h>

#define max(a, b) ((a)>(b)?(a):(b))

void normal(mpz_t n, mpz_t a, mpz_t b, mpz_t x, mpz_t y)
{
    mpz_t pa, pb;
    mpz_init_set_ui(pa, 1);
    mpz_init_set_ui(pb, 1);

    auto kx = mpz_sizeinbase(x, 2);
    auto ky = mpz_sizeinbase(y, 2);

    auto time1 = clock();

    for (int i = kx - 1; i >= 0; i--)
    {
        mpz_mul(pa, pa, pa);
        mpz_mod(pa, pa, n);
        if (mpz_tstbit(x, i))
        {
            mpz_mul(pa, pa, a);
            mpz_mod(pa, pa, n);
        }
    }

    for (int i = ky - 1; i >= 0; i--)
    {
        mpz_mul(pb, pb, pb);
        mpz_mod(pb, pb, n);
        if (mpz_tstbit(y, i))
        {
            mpz_mul(pb, pb, b);
            mpz_mod(pb, pb, n);
        }
    }

    mpz_mul(pa, pa, pb);
    mpz_mod(pa, pa, n);

    auto time2 = clock();
    printf("%lfs\n", difftime(time2, time1) / CLOCKS_PER_SEC);
    gmp_printf("%Zd\n", pa);

    mpz_clears(pa, pb, NULL);
}

void faster(mpz_t n, mpz_t a, mpz_t b, mpz_t x, mpz_t y)
{
    mpz_t p;
    mpz_init_set_ui(p, 1);

    auto kx = mpz_sizeinbase(x, 2);
    auto ky = mpz_sizeinbase(y, 2);

    auto time1 = clock();

    for (int i = max(kx, ky) - 1; i >= 0; i--)
    {
        mpz_mul(p, p, p);
        mpz_mod(p, p, n);
        if (mpz_tstbit(x, i))
        {
            mpz_mul(p, p, a);
            mpz_mod(p, p, n);
        }
        if (mpz_tstbit(y, i))
        {
            mpz_mul(p, p, b);
            mpz_mod(p, p, n);
        }

    }

    auto time2 = clock();
    printf("%lfs\n", difftime(time2, time1) / CLOCKS_PER_SEC);
    gmp_printf("%Zd\n", p);

    mpz_clear(p);
}


int main()
{
    gmp_randstate_t randstate = {};
    gmp_randinit_mt(randstate);
    gmp_randseed_ui(randstate, (unsigned) time(NULL));

    mpz_t n, a, b, x, y;
    mpz_inits(n, a, b, x, y, NULL);
    mpz_urandomb(n, randstate, 32768);
    mpz_urandomb(a, randstate, 16384);
    mpz_urandomb(b, randstate, 16384);
    mpz_urandomb(x, randstate, 16384);
    mpz_urandomb(y, randstate, 16384);

    normal(n, a, b, x, y);
    faster(n, a, b, x, y);


    mpz_clears(n, a, b, x, y, NULL);

    return 0;
}
