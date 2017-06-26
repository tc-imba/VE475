//
// Created by liu on 17-6-26.
//

#include <cstdint>
#include <iostream>
#include <fstream>

using namespace std;

void continued_frac(uint64_t p, uint64_t q)
{
    ofstream out("1.tex");
    uint64_t h1 = 1, k1 = 0, h2 = 0, k2 = 1;
    size_t i = 0;
    while (q >= 1)
    {
        auto d = p / q;
        auto h = d * h1 + h2;
        auto k = d * k1 + k2;

        out << i++ << " & " << d << " & " << h << " & " << k << " \\\\" << endl;

        h2 = h1;
        h1 = h;
        k2 = k1;
        k1 = k;

        d = p % q;
        p = q;
        q = d;
    }
    out.close();
}

int main()
{
    continued_frac(77537081, 317940011);

    return 0;
}