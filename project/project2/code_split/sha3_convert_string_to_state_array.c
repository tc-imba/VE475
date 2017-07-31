void sha3_convert_string_to_state_array(sha3_string S, sha3_state_array A, sha3_bits b, size_t r)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < SHA3_WIDTH[b]; k++)
            {
                size_t index = SHA3_WIDTH[b] * (5 * j + i) + k;
                A[i][j][k] = index < r ? S[index] : (uint8_t) 0;
            }
        }
    }
}
