//
// Created by liu on 17-7-12.
//

#ifndef VE475_RC4_H
#define VE475_RC4_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <memory.h>


#define RC5_MASK 0xffffffffL
#define RC5_P    0xB7E15163L
#define RC5_Q    0x9E3779B9L

#define ROTATE_LEFT(a, n)     (((a)<<(int)(n))|((a)>>(32-(int)(n))))
#define ROTATE_RIGHT(a, n)     (((a)>>(int)(n))|((a)<<(32-(int)(n))))

uint8_t *rc5_encode(const uint8_t text[], const uint32_t key[]);

uint8_t *rc5_decode(const uint8_t text[], const uint32_t key[]);

uint32_t *rc5_generate_key(const uint8_t *data, const uint32_t &len);

#endif //VE475_RC4_H
