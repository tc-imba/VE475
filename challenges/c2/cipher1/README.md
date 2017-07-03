## Introduction

This cipher is based on AES (which we learnt on the class). It is known that AES uses blocks of 128-bits, that is, an array of uint8_t, size of 16, in this implementation.

## Usage
```
usage: c2 [ --generate | --encrypt <message> --key <key> | --decrypt <message> --key <key> ]
arguments:
	--generate: generate generate a key
	--encrypt: encrypt a message
	--decrypt: decrypt a message
	--key: use the specified key to encrypt or decrypt
```

## Transform of strings
We use a very simple method to transform strings. First, there is a array of all available chars, and the reverse of them, in `type.h`. Then according to these four functions:
```
std::vector<uint8_t> byte_encode(const std::string &str);
std::string byte_decode(const std::vector<uint8_t> &bytes);
std::vector<uint8_t> byte_encode_double(const std::string &str);
std::string byte_decode_double(const std::vector<uint8_t> &bytes);
```
A string of right form of input can be transformed into a vector of bytes with `byte_encode`, and such bytes can be transformed back through `byte_decode`.

However, in the AES result, we will get bytes larger than 69 (the number of available characters), so we simply save them in two chars. A ciphertext can be transformed into bytes with `byte_encode_double`, and the ciphered bytes can be transformed into ciphertext with `byte_decode_double`. Note that a random factor is mixed in to make the ciphertext looks good, with no other usage.

## Addition
The blocks are ciphered with CBC Mode, which is also introduced in class, so there is no need to explain details about it.
