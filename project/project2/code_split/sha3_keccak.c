inline sha3_string sha3_keccak(sha3_input N, size_t N_len, size_t d, size_t c)
{
    return sha3_sponge(N, N_len, d, SHA3_BITS_1600, 25 * SHA3_WIDTH[SHA3_BITS_1600] - c);
}
