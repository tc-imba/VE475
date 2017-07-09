#include <iostream>
#include <cstdint>

using namespace std;


uint64_t gcd(uint64_t a, uint64_t b)
{
    if (b == 0)return a;
    return gcd(b, a % b);
}

inline uint64_t func(uint64_t a, uint64_t n)
{
    return (a * a + 1) % n;
}

uint64_t pollard_rho(uint64_t n)
{
    uint64_t a = 2, b = 2, d = 1;
    while (d == 1)
    {
        a = func(a, n);
        b = func(func(b, n), n);
        d = gcd(a > b ? a - b : b - a, n);
    }
    return d;
}


int main()
{
    uint64_t n;
    cout << "Please input a number: ";
    cin >> n;
    cout << n << " = ";
    if (n > 1)
    {
        while (true)
        {
            auto d = pollard_rho(n);
            if (d == n)
            {
                cout << d;
                break;
            } else
            {
                cout << d << " x ";
                n /= d;
            }
        }
    }
    return 0;
}
