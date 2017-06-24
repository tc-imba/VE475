//
// Created by liu on 17-6-18.
//

#include "mod_exp.h"
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

void mod_exp(unsigned int m, unsigned int p, unsigned int n, const char* filename)
{
    list<unsigned int> d;
    while (p > 0)
    {
        d.push_front(p % 2);
        p /= 2;
    }
    unsigned int power = 1;
    auto i = d.size() - 1;
    ofstream out(filename);
    out << "\\begin{center}" << endl
        << "\\begin{tabular}{c|c|c}"<<  endl
        << "$i$ & $d_i$ & power mod " << n << " \\\\\\hline " << endl;
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
    out << "\\end{tabular}\n\\end{center}" << endl;

    out.close();
}