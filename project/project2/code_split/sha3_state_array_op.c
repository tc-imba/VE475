void sha3_state_array_op(sha3_state_array origin, sha3_state_array other, sha3_bits b, uint8_t (*fn)(uint8_t, uint8_t))
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < SHA3_WIDTH[b]; k++)
            {
                origin[i][j][k] = fn(origin[i][j][k], other[i][j][k]);
            }
        }
    }
}
