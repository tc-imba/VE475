void sha3_destroy_state_array(sha3_state_array A)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);
}
