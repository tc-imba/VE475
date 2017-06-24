//
// Created by liu on 17-6-24.
//

#include "ext_euclid.h"
#include <iostream>
#include <fstream>

using namespace std;

void ext_euclid(int p, int q, const char *filename, bool detail)
{
    ofstream out(filename);
    pair<int, int> r(p, q), s(1, 0), t(0, 1);
    out << "\\begin{center}" << endl
        << "\\begin{tabular}{|c|c|c|c|" << (detail ? "c|}" : "}") << endl
        << "\\hline & $q_i$ & $r_i$ & $s_i$" << (detail ? " & $t_i$" : "") << " \\\\\\hline" << endl;
    out << "0 & & " << r.first << " & " << s.first;
    if (detail)out << " & " << t.first;
    out << " \\\\\\hline" << endl;
    out << "1 & & " << r.second << " & " << s.second;
    if (detail)out << " & " << t.second;
    out << " \\\\\\hline" << endl;
    int i = 2;
    while (r.second > 1)
    {
        int d = r.first / r.second;
        out << i++ << " & ";
        out << "$ " << r.first << "\\div" << r.second << "=" << d << "$ & ";

        out << "$" << r.first << "-" << d << "\\times" << r.second << "=";
        r = make_pair(r.second, r.first - d * r.second);
        out << r.second << "$";

        out << " & ";

        out << "$" << s.first << "-" << d << "\\times" << s.second << "=";
        s = make_pair(s.second, s.first - d * s.second);
        out << s.second << "$";

        if (detail)
        {
            out << " & ";
            out << "$" << t.first << "-" << d << "\\times" << t.second << "=";
            t = make_pair(t.second, t.first - d * t.second);
            out << t.second << "$";
        }

        out << " \\\\\\hline" << endl;
    }

    out << "\\end{tabular}\n\\end{center}" << endl;
    out.close();
}
