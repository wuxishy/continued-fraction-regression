/***********************
 * FILE: mutate_op.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "gp.hpp"

#include "fraction.hpp"
#include "func.hpp"

void population::feature_toggle(fraction& frac) {
    int i = rint(0, frac.repr.size()-1);
    int j = rint(0, frac.repr[i].num_var - 1);

    // turn off the feature
    if(frac.repr[i].feature[j]) {
        frac.repr[i].coeff[j] = 0;
        frac.repr[i].feature[j] = false;
    }
    // turn on the feature
    else {
        frac.repr[i].coeff[j] = (rint(0, 1) ? 1 : -1) * rint(1, 3);
        frac.repr[i].feature[j] = true;
    }
}
