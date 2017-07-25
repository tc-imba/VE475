//
// Created by liu on 17-7-25.
//

#include "sha3.h"

int main()
{
    sha3_state_array A;
    sha3_init_state_array(&A, SHA3_BITS_1600);

    sha3_step_rho(A, SHA3_BITS_1600);

    for (int i = 0; i < 255; i++)
    {
        uint8_t R[9] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int j = 1; j <= i; j++)
        {
            for (int k = 8; k > 0; k--) R[k] = R[k - 1];
            R[0] = 0;
            R[0] ^= R[8];
            R[4] ^= R[8];
            R[5] ^= R[8];
            R[6] ^= R[8];
        }
        printf("%d,", R[0]);
        if (i % 16 == 15)printf("\n");
    }

    sha3_destroy_state_array(A);
    return 0;
}