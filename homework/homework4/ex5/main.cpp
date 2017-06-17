//
// Created by liu on 17-6-18.
//

#include <iostream>
#include <fstream>
#include <list>

using namespace std;

int main()
{
    unsigned int m = 3;
    unsigned int p = 32768;
    unsigned int n = 65537;
    list<unsigned int> d;
    while (p > 0)
    {
        d.push_front(p % 2);
        p /= 2;
    }
    unsigned int power = 1;
    auto i = d.size() - 1;
    ofstream out("2.tex");
    for (auto &it:d)
    {
        out << i-- << " & " << it << " & $" << power << "^2";
        power = (power * power) % n;
        if (it == 1)
        {
            out << " \\cdot " << m;
            power = (m * power) % n;
        }
        out << " \\equiv " << power << "$ \\\\" << endl;
    }
}