//
// Created by liu on 17-7-3.
//

#ifndef VE475_BYTE_H
#define VE475_BYTE_H

#include <cstdint>
#include <string>
#include <vector>

const size_t alphabet_size = 69;
static const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.;?!()";
static uint8_t alphabet_rev[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0, 0, 0, 0, 66, 0, 0, 0, 0, 0, 0, 67, 68, 0, 0, 62, 0, 63, 0, 52, 53, 54, 55, 56,
                                 57, 58, 59, 60, 61, 0, 64, 0, 0, 0, 65, 0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
                                 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0, 0, 0,
                                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                                 24, 25, 0, 0, 0, 0, 0};

std::vector<uint8_t> byte_encode(const std::string &str);

std::string byte_decode(const std::vector<uint8_t> &bytes);

std::vector<uint8_t> byte_encode_double(const std::string &str);

std::string byte_decode_double(const std::vector<uint8_t> &bytes);

#endif //VE475_BYTE_H
