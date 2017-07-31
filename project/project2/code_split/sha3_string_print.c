void sha3_string_print(sha3_string S, size_t length)
{
    for (int i = 0; i < length; i += 4)
    {
        printf("%X", S[i] * 8 + S[i + 1] * 4 + S[i + 2] * 2 + S[i + 3]);
    }
    printf("\n");
}
