inline void sha3_step_chi(sha3_state_array A, sha3_bits b)
{
    for (int k = 0; k < SHA3_WIDTH[b]; k++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 5; i++)
            {
                sha3_temp[0][i] = A[i][j][k] ^ ((A[(i + 1) % 5][j][k] ^ (uint8_t) 1) & A[(i + 2) % 5][j][k]);
            }
            for (int i = 0; i < 5; i++)
            {
                A[i][j][k] = sha3_temp[0][i];
            }
        }
    }
}
