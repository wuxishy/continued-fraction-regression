/**********************
 * FILE: func.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#include "func.hpp"

#include "rng.hpp"
#include <iostream>

func::func(std::size_t n) : num_var(n) {
    coeff = std::vector<double> (n);
    feature = std::vector<bool> (n, true);

    randint rint;
    for(std::size_t i = 0; i < n; ++i) {
        coeff[i] = rint(-3, 3);
        if (coeff[i] == 0) feature[i] = false; 
    }
}

void func::find_feature() {
    for(std::size_t i = 0; i < coeff.size(); ++i) {
        if(std::abs(coeff[i]) < eps) {
            coeff[i] = 0;
            feature[i] = false;
        }
        else feature[i] = true;
    }
}

double func::eval(const std::vector<double>& vars) {
    double ret = 0;

    for(std::size_t i = 0; i < num_var; ++i) {
        ret += vars[i] * coeff[i];
    }

    return ret;
}

void func::show(std::ostream& out) {
    out << "(" << coeff[0];
    
    for(std::size_t i = 1; i < num_var; ++i) {
        out << ", " << coeff[i];
    }

    out <<  ")";
}
