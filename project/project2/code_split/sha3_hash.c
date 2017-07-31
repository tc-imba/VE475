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
