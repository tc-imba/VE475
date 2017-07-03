//
// Created by liu on 17-7-3.
//

#include <iostream>
#include <cstring>
#include <cstdint>
#include <string>

#include "byte.h"

extern "C"
{
#include "aes.h"
}


using namespace std;

uint8_t *getKeyBytes(const string &key)
{
    auto k = byte_encode(key);
    auto k_ = new uint8_t[8];
    for (int i = 0; i < 8; i++)
    {
        if (i < k.size())k_[i] = k[i];
        k_[i] = 0;
    }
    return k_;
}

void help()
{
    cout << "usage: c2 [ --generate | --encrypt <message> --key <key> | --decrypt <message> --key <key> ]" << endl
         << "arguments: " << endl
         << "\t--generate: generate generate a key" << endl
         << "\t--encrypt: encrypt a message" << endl
         << "\t--decrypt: decrypt a message" << endl
         << "\t--key: use the specified key to encrypt or decrypt" << endl;
}

string generate()
{
    srand(time(0));
    string str;
    for (int i = 0; i < 16; i++)
    {
        str.push_back(alphabet[rand() % alphabet_size]);
    }
    return str;
}

string encrypt(const string &message, const string &key)
{
    auto m = byte_encode(message);
    auto k = getKeyBytes(key);
    uint8_t trim = (m.size() + 1) % 16;
    if (trim > 0) trim = 16 - trim;
    m.insert(m.begin(), trim);
    for (int i = 0; i < trim; i++) m.push_back(0);
    vector<uint8_t> result(m.size());
    for (int i = 0; i < m.size(); i += 16)
    {
        uint8_t m_[16] = {};
        for (int j = 0; j < 16; j++)
        {
            m_[j] = m[i + j];
            if (i > 0)m_[j] ^= result[i + j - 16];
        }
        auto c = aes_encode(m_, k);
        for (int j = 0; j < 16; j++)
        {
            result[i + j] = c[j];
        }
        delete[] c;
    }
    delete[] k;
    return byte_decode_double(result);
}

string decrypt(const string &ciphertext, const string &key)
{
    string str;
    auto c = byte_encode_double(ciphertext);
    auto k = getKeyBytes(key);
    uint8_t trim = c.size() % 16;
    if (trim > 0)for (int i = 0; i < 16 - trim; i++)c.push_back(0);
    vector<uint8_t> result(c.size());
    for (int i = c.size() - 16; i >= 0; i -= 16)
    {
        uint8_t c_[16] = {};
        for (int j = 0; j < 16; j++)
        {
            c_[j] = c[i + j];
            if (i < c.size() - 16)result[i + j + 16] ^= c_[j];
        }
        auto m = aes_decode(c_, k);
        for (int j = 0; j < 16; j++)
        {
            result[i + j] = m[j];
        }
        delete[] m;
    }
    str = byte_decode(result);
    trim = alphabet_rev[str[0]];
    str.erase(0, 1);
    for (int i = 0; i < trim; i++) str.pop_back();
    return str;
}


int main(int argc, char *argv[])
{
    /*cout << encrypt("fhruisgboikufgdsbikgsbkjfdg", "dsfhuifgdhbksfgdbnkjg") << endl;
    cout << decrypt("zXAtPxtmvmm)pVAjLVNUygYd25WvfM4vDgES6eK9Vjjz8JupxN9y5EvIBD1v41ZB",
                    "dsfhuifgdhbksfgdbnkjg");
*/
    if (argc <= 1) help();
    else if (strcmp(argv[1], "--generate") == 0) cout << generate() << endl;
    else if (argc <= 4) help();
    else if (strcmp(argv[1], "--encrypt") == 0 && strcmp(argv[3], "--key") == 0)
        cout << encrypt(argv[2], argv[4]) << endl;
    else if (strcmp(argv[1], "--decrypt") == 0 && strcmp(argv[3], "--key") == 0)
        cout << decrypt(argv[2], argv[4]) << endl;
    else help();
    return 0;
}