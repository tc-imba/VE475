//
// Created by liu on 17-7-25.
//

#include "sha3.h"
#include <time.h>
#include <stdio.h>

void generate_rc()
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

int main()
{
    //srand(time(0));
    int count = 1;
    int mb = 1 << 23; //1 MB
    int size = 1;
    size_t length = mb * size;
    double t = 0;

    for (int i = 0; i < count; i++)
        t += sha3_test(length);

    printf("The average running time is %lf MB/s\n", size / (t / CLOCKS_PER_SEC / count));

    return 0;
}