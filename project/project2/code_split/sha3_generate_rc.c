void sha3_generate_rc()
{
    for (int i = 0; i < 255; i++)
    {
        uint8_t R[9] = {1, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int j = 1; j <= i; j++)
        {
            for (int k = 8; k > 0; k--) R[k] = R[k - 1];
            R[0] = 0;
            R[0] ^= R[8];
            R[4] ^= R[8];
            R[5] ^= R[8];
            R[6] ^= R[8];
        }
        printf("%d,", R[0]);
        if (i % 16 == 15)printf("\n");
    }
    printf("\n");
}
