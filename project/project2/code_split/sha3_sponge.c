sha3_string sha3_sponge(sha3_input N, size_t N_len, size_t d, sha3_bits b, size_t r)
{
    size_t m = r - N_len % r;
    if (m <= 2)m += r;
    size_t P_len = N_len + m;
    sha3_input P = malloc(sizeof(uint8_t) * P_len);
    memcpy(P, N, sizeof(uint8_t) * N_len);
    memset(P + N_len + 1, 0, sizeof(uint8_t) * (m - 2));
    P[N_len] = P[P_len - 1] = 1;
    size_t n = P_len / r;
    sha3_state_array A, B;
    sha3_init_state_array(&A, b);
    sha3_init_state_array(&B, b);
    for (int i = 0; i < P_len; i += r)
    {
        sha3_convert_string_to_state_array(P + i, B, b, r);
        sha3_state_array_op(A, B, b, sha3_xor);
        sha3_keccak_f(A, b);
    }
    sha3_string S = malloc(sizeof(uint8_t) * SHA3_WIDTH[b] * 25);
    sha3_string Z = malloc(sizeof(uint8_t) * d);
    size_t offset = 0;
    while (offset < d)
    {
        sha3_convert_state_array_to_string(A, S, b);
        memcpy(Z + offset, S, r < d - offset ? r : d - offset);
        offset += r;
        sha3_keccak_f(A, b);
    }
    sha3_destroy_state_array(A);
    sha3_destroy_state_array(B);
    free(S);
    free(P);
    return Z;
}
