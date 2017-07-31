inline void sha3_step_iota(sha3_state_array A, sha3_bits b, size_t ir)
{
    for (int j = 0; j < b; j++)
    {
        A[0][0][SHA3_WIDTH[j] - 1] ^= SHA3_RC[(j + 7 * ir) % 0xFF];
    }
}
