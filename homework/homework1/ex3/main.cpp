//
// Created by liu on 17-5-20.
//

#include <gmp.h>

using namespace std;

mpz_t getRandomInt() {
    mpz_t a;
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_init(a);
    mpz_urandomb(a, state, 4096);
    return a;
}

int main() {
    auto a=getRandomInt();
    mpz_t a, b;
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_init(a);
    mpz_urandomb(a, state, 4096);
    mpz_out_str(stdout, 10, a);
    return 0;
}