void sha3_state_array_print(sha3_state_array A, sha3_bits b)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < SHA3_WIDTH[b]; k++)
            {
                printf("%d\t", A[i][j][k]);
            }
            printf("\n");
        }
    }
    printf("\n");
}
