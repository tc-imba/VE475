inline void sha3_keccak_f(sha3_state_array A, sha3_bits b)
{
    sha3_keccak_p(A, b, b * 2 + 12);
}
