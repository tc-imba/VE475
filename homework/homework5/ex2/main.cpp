//
// Created by liu on 17-6-18.
//

#include "../mod_exp/mod_exp.h"
#include "../ext_euclid/ext_euclid.h"

int main()
{
    ext_euclid(7467, 11413, "1.tex");
    mod_exp(5859, 7546, 11413, "2.tex");
    return 0;
}