inline void sha3_step_rho(sha3_state_array A, sha3_bits b)
{
    uint8_t x = 1, y = 0;
    uint8_t *B = sha3_temp[0];
    for (int t = 0; t < 24; t++)
    {
        uint8_t temp = ((-(t + 1) * (t + 2) / 2) % SHA3_WIDTH[b] + SHA3_WIDTH[b]) % SHA3_WIDTH[b];
        memcpy(B, A[x][y] + SHA3_WIDTH[b] - temp, sizeof(uint8_t) * temp);
        memcpy(A[x][y] + temp, A[x][y], sizeof(uint8_t) * (SHA3_WIDTH[b] - temp));
        memcpy(A[x][y], B, sizeof(uint8_t) * temp);
        temp = (2 * x + 3 * y) % 5;
        x = y;
        y = temp;
    }
}
