inline void sha3_step_theta(sha3_state_array A, sha3_bits b)
{
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < SHA3_WIDTH[b]; k++)
        {
            sha3_temp[i][k] = A[i][0][k];
            for (int j = 1; j < 5; j++)
            {
                sha3_temp[i][k] ^= A[i][j][k];
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < SHA3_WIDTH[b]; k++)
        {
            uint8_t D = sha3_temp[(i + 4) % 5][k] ^sha3_temp[(i + 1) % 5][(k - 1 + SHA3_WIDTH[b]) % SHA3_WIDTH[b]];
            for (int j = 0; j < 5; j++)
            {
                A[i][j][k] ^= D;
            }
        }
    }
}
