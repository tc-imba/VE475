//
// Created by liu on 17-7-25.
//

#include "sha3.h"

int main()
{
    sha3_state_array A;
    sha3_init_state_array(&A, SHA3_BITS_1600);

    sha3_step_rho(A, SHA3_BITS_1600);

    sha3_destroy_state_array(A);
    return 0;
}