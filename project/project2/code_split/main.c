int main()
{
    int count = 8;
    size_t mb = 1 << 23;
    size_t size = 1;
    size_t length = mb * size;
    double t = 0;
    for (int i = 0; i < count; i++)
        t += sha3_test(length);
    printf("The average running speed is %lf MB/s\n", size / (t / CLOCKS_PER_SEC / count));
    return 0;
}