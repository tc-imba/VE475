double sha3_test(size_t length)
{
    sha3_string M = malloc(length);
    for (int i = 0; i < length; i++)
    {
        M[i] = rand() % 2;
    }
    long time1 = clock();
    sha3_string result = sha3_hash(M, length, SHA3_512);
    long time2 = clock();
    sha3_string_print(result, 512);
    free(M);
    free(result);
    return difftime(time2, time1);
}
