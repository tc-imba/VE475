void sha3_init_state_array(sha3_state_array *A, sha3_bits b)
{
    *A = calloc(sizeof(uint8_t **), 5);
    for (int i = 0; i < 5; i++)
    {
        (*A)[i] = calloc(sizeof(uint8_t *), 5);
        for (int j = 0; j < 5; j++)
        {
            (*A)[i][j] = calloc(sizeof(uint8_t), SHA3_WIDTH[b]);
        }
    }
}
