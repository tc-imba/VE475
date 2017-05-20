//
// Created by liu on 17-5-20.
//

#include <gmp.h>

using namespace std;

int main() {

    mpz_t a, b;
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_urandomb(a, 0, 4096);
    mpz_out_str(stdout, 10, a);
    return 0;
}