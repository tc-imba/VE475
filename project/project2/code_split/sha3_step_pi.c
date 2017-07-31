inline void sha3_step_pi(sha3_state_array A, sha3_bits b)
{
    for (int k = 0; k < SHA3_WIDTH[b]; k++)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                sha3_temp[i][j] = A[(i + 3 * j) % 5][i][k];
            }
        }
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                A[i][j][k] = sha3_temp[i][j];
            }
        }
    }
}
