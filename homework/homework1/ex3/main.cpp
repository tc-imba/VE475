//
// Created by liu on 17-5-20.
//

#include <gmpxx.h>
#include <iostream>
#include <ctime>

std::pair<mpz_class, std::pair<mpz_class, mpz_class> >
extended_euclidean_algorithm(const mpz_class &a, const mpz_class &b)
{
    std::pair<mpz_class, mpz_class> r(b, a), s(1, 0), t(0, 1);
    while (r.first != 0)
    {
        mpz_class q = r.second / r.first;
        r = std::make_pair(r.second - q * r.first, r.first);
        s = std::make_pair(s.second - q * s.first, s.first);
        t = std::make_pair(t.second - q * t.first, t.first);
    }
    return std::make_pair(r.second, std::make_pair(s.second, t.second));
}

int main()
{
    gmp_randclass randclass(gmp_randinit_default);
    randclass.seed((unsigned long) time(nullptr));

    mpz_class numA = randclass.get_z_bits(4096);
    mpz_class numB = randclass.get_z_bits(4096);

    mpz_class libResult = gcd(numA, numB);
    mpz_class result = extended_euclidean_algorithm(numA, numB).first;

    std::cout << "Integer a: " << numA << std::endl;
    std::cout << "Integer b: " << numB << std::endl;
    std::cout << "gcd(a,b) with GMP Library: " << libResult << std::endl;
    std::cout << "gcd(a,b) with extended Euclidean algorithm: " << result << std::endl;

    if (result == libResult) std::cout << "The results are identical" << std::endl;
    else std::cout << "Oops! The results are different" << std::endl;

    return 0;
}