/**********************
 * FILE: func.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#include "func.hpp"
#include "rng.hpp"
func::func(std::size_t n) : num_var(n) {
    coeff = std::vector<double> (n);

    // just random stuff for now
    randint r(0, 9);
    coeff[0] = r();
}

double func::eval(std::vector<double>& vars) {
    double ret = 0;

    for(std::size_t i = 0; i < num_var; ++i) {
        ret += vars[i] * coeff[i];
    }

    return ret;
}
