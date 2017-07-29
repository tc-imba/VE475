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

void sha3_state_array_print(sha3_state_array A, sha3_bits b)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < SHA3_WIDTH[b]; k++)
            {
                printf("%d\t", A[i][j][k]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

void sha3_string_print(sha3_string S, size_t length)
{
    for (int i = 0; i < length; i += 4)
    {
        printf("%X", S[i] * 8 + S[i + 1] * 4 + S[i + 2] * 2 + S[i + 3]);
    }
    printf("\n");
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
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 5; i++)
            {
                sha3_temp[0][i] = A[i][j][k] ^ ((A[(i + 1) % 5][j][k] ^ (uint8_t) 1) & A[(i + 2) % 5][j][k]);
            }
            for (int i = 0; i < 5; i++)
            {
                A[i][j][k] = sha3_temp[0][i];
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

void sha3_state_array_op(sha3_state_array origin, sha3_state_array other, sha3_bits b, uint8_t (*fn)(uint8_t, uint8_t))
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < SHA3_WIDTH[b]; k++)
            {
                origin[i][j][k] = fn(origin[i][j][k], other[i][j][k]);
            }
        }
    }
}

inline uint8_t sha3_xor(uint8_t a, uint8_t b)
{
    return a ^ b;
}

sha3_string sha3_sponge(sha3_input N, size_t N_len, size_t d, sha3_bits b, size_t r)
{
    // Padding
    size_t m = r - N_len % r;
    if (m <= 2)m += r;
    size_t P_len = N_len + m;
    sha3_input P = malloc(sizeof(uint8_t) * P_len);
    memcpy(P, N, sizeof(uint8_t) * N_len);
    memset(P + N_len + 1, 0, sizeof(uint8_t) * (m - 2));
    P[N_len] = P[P_len - 1] = 1;
    size_t n = P_len / r;

    // Rounds
    sha3_state_array A, B;
    sha3_init_state_array(&A, b);
    sha3_init_state_array(&B, b);

    for (int i = 0; i < P_len; i += r)
    {
        sha3_convert_string_to_state_array(P + i, B, b, r);
        sha3_state_array_op(A, B, b, sha3_xor);
        sha3_keccak_f(A, b);
        //sha3_state_array_print(A, b);
    }

    // Output
    sha3_string S = malloc(sizeof(uint8_t) * SHA3_WIDTH[b] * 25);
    sha3_string Z = malloc(sizeof(uint8_t) * d);
    size_t offset = 0;
    while (offset < d)
    {
        sha3_convert_state_array_to_string(A, S, b);
        memcpy(Z + offset, S, r < d - offset ? r : d - offset);
        offset += r;
        sha3_keccak_f(A, b);
    }

    // Clear
    sha3_destroy_state_array(A);
    sha3_destroy_state_array(B);
    free(S);
    free(P);
    return Z;
}

inline sha3_string sha3_keccak(sha3_input N, size_t N_len, size_t d, size_t c)
{
    return sha3_sponge(N, N_len, d, SHA3_BITS_1600, 25 * SHA3_WIDTH[SHA3_BITS_1600] - c);
}

inline sha3_string sha3_hash(sha3_input M, size_t M_len, sha3_mode mode)
{
    if (mode < 0 || mode > SHA3_512) mode = SHA3_224;
    size_t N_len = M_len + 2;
    sha3_input N = malloc(sizeof(uint8_t) * N_len);
    memcpy(N, M, M_len);
    N[M_len] = 0;
    N[M_len + 1] = 1;
    sha3_string S = sha3_keccak(N, N_len, SHA3_MODE_LEN[mode], SHA3_MODE_LEN[mode] * 2);
    free(N);
    return S;
}




