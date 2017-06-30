# Ex.4 Readme File

## Compilation

This program is written in c++, built and tested under Linux (Ubuntu 17.04), with cmake > 3.5, and the GMP Library is used. It can be installed by
```
$ sudo apt-get install libgmp-dev
```
The CMakeLists file will find `libgmp.so` and `libgmpxx.so` under `/usr/lib` if you've installed it correctly.

You can generate the Makefile by
```
$ sudo apt-get install cmake
$ cmake ./
```
You need to generate it yourself due to some cross-platform issues. (You can also use the Makefile in this directory, but perhaps it won't work)

## Description

This is a implementation of RSA key generation, encyption and decryption. There are three functions exported to be used:

```
rsa_key rsa_generate(RSA_SECURITY security);
rsa_pair rsa_encrypt(uint8_t *m_bytes, size_t m_size, uint8_t *n_bytes, size_t n_size, uint8_t *e_bytes, size_t e_size);
rsa_pair rsa_decrypt(uint8_t *c_bytes, size_t c_size, uint8_t *n_bytes, size_t n_size, uint8_t *d_bytes, size_t d_size);
```

First, you can call the function `rsa_generate` and with the security level defined, and get a struct of generated key:
```
typedef struct rsa_key_t
{
    RSA_SECURITY security;
    uint8_t *p, *q, *n, *d, *e;
    size_t p_size, q_size, n_size, d_size, e_size;
} rsa_key;
```

Then you can use the generated `n` and `e` to encrypt some plaintext which is smaller than `n`, with the function `rsa_encrypt`, and get a struct of `uint8_t` data:


You may find some information about the functions in the header file (`rsa.h`).
```
typedef struct rsa_pair_t
{
    uint8_t *bytes;
    size_t size;
} rsa_pair;
```

Also you can use the generated `n` and d` ti decrypt some ciphertext which is smaller than `n`, with the function `rsa_decrypt`, and get a same struct as `rsa_encrypt`.

By the way, you can use
```
void rsa_key_free(rsa_key key);
void rsa_pair_free(rsa_pair pair);
void rsa_bytes_print(uint8_t *bytes, size_t size, FILE *stream);
void rsa_key_print(rsa_key key, FILE *stream);
```

to check your key and data, or free the memory.

The program was checked by `valgrind` with not memory leaked.

Note that this is only a naive implementation of textbook RSA, which is not very efficient and secure enough. In the main file, a simple test is applied: (all of the data is in hex)

The plaintext is `0123456789abcdeffedcba9876543210`.

The key is randomly generated.

Then you can compare the ciphertext and the decypted plaintext, which is identical to the origin plaintext.
