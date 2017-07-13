//
// Created by liu on 17-7-3.
//

#include "byte.h"
#include <iostream>
#include <ctime>

using namespace std;

std::vector<uint8_t> byte_encode(const std::string &str)
{
    vector<uint8_t> bytes;
    for (int i = 0; i < str.length(); i++)
    {
        bytes.push_back(alphabet_rev[str[i]]);
    }
//    for (auto &it:bytes)
//        cout << int(it) << "\t";
//    cout << endl;
    return bytes;
}

std::string byte_decode(const std::vector<uint8_t> &bytes)
{
    string str;
    for (int i = 0; i < bytes.size(); i++)
    {
        str.push_back(alphabet[bytes[i] % alphabet_size]);
    }
//    cout << str << endl;
    return str;
}

std::vector<uint8_t> byte_encode_double(const std::string &str)
{
    vector<uint8_t> bytes;
    for (int i = 0; i < str.length(); i += 2)
    {
        bytes.push_back(alphabet_rev[str[i]] % 4 * alphabet_size + alphabet_rev[str[i + 1]]);
    }
//    for (auto &it:bytes)
//        cout << int(it) << "\t";
//    cout << endl;
    return bytes;
}

std::string byte_decode_double(const std::vector<uint8_t> &bytes)
{
    srand(time(0));
    string str;
    for (int i = 0; i < bytes.size(); i++)
    {
        str.push_back(alphabet[bytes[i] / alphabet_size + 4 * (rand() % 16)]);
        str.push_back(alphabet[bytes[i] % alphabet_size]);
    }
    //cout << str << endl;
    return str;
}

