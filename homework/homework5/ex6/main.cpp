//
// Created by liu on 17-6-18.
//

#include "../mod_exp/mod_exp.h"

int main()
{
    mod_exp(3, 2048, 65537, "1.tex");
    mod_exp(3, 2048*31, 65537, "2.tex");
    return 0;
}
