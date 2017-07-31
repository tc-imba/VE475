inline void sha3_keccak_p(sha3_state_array A, sha3_bits b, size_t nr)
{
    for (size_t i = 1; i <= nr; i++)
    {
        sha3_rnd(A, b, 12 + 2 * b - i);
    }
}
