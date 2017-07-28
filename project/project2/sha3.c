//
// Created by liu on 17-7-25.
//

#include "sha3.h"

void sha3_init_state_array(sha3_state_array *A, sha3_bits b)
{
    *A = calloc(sizeof(uint8_t **), 5);
    for (int i = 0; i < 5; i++)
    {
        (*A)[i] = calloc(sizeof(uint8_t *), 5);
        for (int j = 0; j < 5; j++)
        {
            (*A)[i][j] = calloc(sizeof(uint8_t), SHA3_WIDTH[b]);
        }
    }
}

void sha3_destroy_state_array(sha3_state_array A)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);
}

void sha3_convert_string_to_state_array(sha3_string S, sha3_state_array A, sha3_bits b, size_t r)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < SHA3_WIDTH[b]; k++)
            {
                size_t index = SHA3_WIDTH[b] * (5 * j + i) + k;
                A[i][j][k] = index < r ? S[index] : (uint8_t) 0;
            }
        }
    }
}

void sha3_convert_state_array_to_string(sha3_state_array A, sha3_string S, sha3_bits b)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < SHA3_WIDTH[b]; k++)
            {
                S[SHA3_WIDTH[b] * (5 * j + i) + k] = A[i][j][k];
            }
        }
    }
}

inline void sha3_step_theta(sha3_state_array A, sha3_bits b)
{
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < SHA3_WIDTH[b]; k++)
        {
            sha3_temp[i][k] = A[i][0][k];
            for (int j = 1; j < 5; j++)
            {
                sha3_temp[i][k] ^= A[i][j][k];
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < SHA3_WIDTH[b]; k++)
        {
            uint8_t D = sha3_temp[(i + 4) % 5][k] ^sha3_temp[(i + 1) % 5][(k - 1 + SHA3_WIDTH[b]) % SHA3_WIDTH[b]];
            for (int j = 0; j < 5; j++)
            {
                A[i][j][k] ^= D;
            }
        }
    }
}

inline void sha3_step_rho(sha3_state_array A, sha3_bits b)
{
    uint8_t x = 1, y = 0;
    uint8_t *B = sha3_temp[0];
    for (int t = 0; t < 24; t++)
    {
        uint8_t temp = ((-(t + 1) * (t + 2) / 2) % SHA3_WIDTH[b] + SHA3_WIDTH[b]) % SHA3_WIDTH[b];
        memcpy(B, A[x][y] + SHA3_WIDTH[b] - temp, sizeof(uint8_t) * temp);
        memcpy(A[x][y] + temp, A[x][y], sizeof(uint8_t) * (SHA3_WIDTH[b] - temp));
        memcpy(A[x][y], B, sizeof(uint8_t) * temp);
        temp = (2 * x + 3 * y) % 5;
        x = y;
        y = temp;
        //printf("%d\t%d\n", x, y);
    }
}

inline void sha3_step_pi(sha3_state_array A, sha3_bits b)
{
    for (int k = 0; k < SHA3_WIDTH[b]; k++)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                sha3_temp[i][j] = A[(i + 3 * j) % 5][i][k];
            }
        }
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                A[i][j][k] = sha3_temp[i][j];
            }
        }
    }
}

inline void sha3_step_chi(sha3_state_array A, sha3_bits b)
{
    for (int k = 0; k < SHA3_WIDTH[b]; k++)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                sha3_temp[i][j] = A[i][j][k] ^ ((A[(i + 1) % 5][j][k] ^ (uint8_t) 1) & A[(i + 2) % 5][j][k]);
            }
        }
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                A[i][j][k] = sha3_temp[i][j];
            }
        }
    }
}

inline void sha3_step_iota(sha3_state_array A, sha3_bits b, size_t ir)
{
    for (int j = 0; j < b; j++)
    {
        A[0][0][SHA3_WIDTH[j] - 1] ^= SHA3_RC[(j + 7 * ir) % 0xFF];
    }
}

inline void sha3_rnd(sha3_state_array A, sha3_bits b, size_t ir)
{
    sha3_step_theta(A, b);
    sha3_step_rho(A, b);
    sha3_step_pi(A, b);
    sha3_step_chi(A, b);
    sha3_step_iota(A, b, ir);
}

inline void sha3_keccak_p(sha3_state_array A, sha3_bits b, size_t nr)
{
    for (size_t i = 1; i <= nr; i++)
    {
        sha3_rnd(A, b, 12 + 2 * b - i);
    }
}

inline void sha3_keccak_f(sha3_state_array A, sha3_bits b)
{
    sha3_keccak_p(A, b, b * 2 + 12);
}


void sha3_sponge(sha3_input N, size_t N_len, size_t d, sha3_bits b, size_t r)
{
    // Padding
    size_t m = N_len % r;
    if (m <= 2)m += r;
    size_t P_len = N_len + m;
    sha3_input P = malloc(sizeof(uint8_t) * P_len);
    memcpy(P, N, sizeof(uint8_t) * N_len);
    memset(P + N_len + 1, 0, sizeof(uint8_t) * (m - 2));
    P[N_len] = P[P_len - 1] = 1;
    size_t n = P_len / r;

    //
    size_t c = SHA3_WIDTH[b] * 25 - r;
    sha3_string S = malloc(sizeof(uint8_t) * SHA3_WIDTH[b]);

    sha3_state_array A;
    sha3_init_state_array(&A, b);

    for (int i = 0; i < P_len; i += r)
    {

        sha3_convert_string_to_state_array(P + i, A, b, r);

    }



    /*sha3_state_array A;
    sha3_init_state_array(&A, SHA3_BITS_1600);
    sha3_convert_string_to_state_array(S, A, b);

    sha3_keccak_f(A, b);

    sha3_convert_state_array_to_string(A, S, b);
    sha3_destroy_state_array(A);*/
}



