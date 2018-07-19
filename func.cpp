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

    randreal rreal;
    for(double& x : coeff) x = 4 * (rreal() - 0.5);
}

double func::eval(std::vector<double>& vars) {
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
