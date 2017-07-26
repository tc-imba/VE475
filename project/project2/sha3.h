//
// Created by liu on 17-7-25.
//

#ifndef VE475_SHA3_H
#define VE475_SHA3_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

typedef enum
{
    SHA3_BITS_25,
    SHA3_BITS_50,
    SHA3_BITS_100,
    SHA3_BITS_200,
    SHA3_BITS_400,
    SHA3_BITS_800,
    SHA3_BITS_1600,
} sha3_bits;

static const size_t SHA3_WIDTH[] = {1, 2, 4, 8, 16, 32, 64};

static const uint8_t SHA3_RC[0xFF] = {
        1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1,
        1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1,
        1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0,
        0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1,
        0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0,
        0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1,
        0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1,
        1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1,
        1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1,
        0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0,
        1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1,
        0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1,
        0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0,
        1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0
};

static uint8_t sha3_temp[5][64] = {};

typedef uint8_t ***sha3_state_array;
typedef uint8_t *sha3_string;

void sha3_init_state_array(sha3_state_array *A, sha3_bits b);

void sha3_destroy_state_array(sha3_state_array A);

void sha3_convert_string_to_state_array(sha3_string S, sha3_state_array A, sha3_bits b);

void sha3_convert_state_array_to_string(sha3_state_array A, sha3_string S, sha3_bits b);

void sha3_step_theta(sha3_state_array A, sha3_bits b);

void sha3_step_rho(sha3_state_array A, sha3_bits b);

void sha3_step_pi(sha3_state_array A, sha3_bits b);

void sha3_step_chi(sha3_state_array A, sha3_bits b);

void sha3_step_iota(sha3_state_array A, sha3_bits b, size_t ir);

void sha3_rnd(sha3_state_array A, sha3_bits b, size_t ir);

void sha3_keccak_p(sha3_state_array A, sha3_bits b, size_t nr);

void sha3_keccak_f(sha3_state_array A, sha3_bits b);


#endif //VE475_SHA3_H
