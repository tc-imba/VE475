## Introduction

This cipher is based on 32-bit RC5.

From Wikipedia, the free encyclopedia

> In cryptography, RC5 is a symmetric-key block cipher notable for its simplicity. Designed by Ronald Rivest in 1994, RC stands for "Rivest Cipher", or alternatively, "Ron's Code" (compare RC2 and RC4). The Advanced Encryption Standard (AES) candidate RC6 was based on RC5.

Some of the details of the algorithm can be found on [wiki - RC5](https://en.wikipedia.org/wiki/RC5)


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

The bash on Ubuntu seems have some bug on recognizing special characters in text, so we recommended you to do encrypt and decrypt testings in the main function. It will be very convenient.