/**********************
 * FILE: func.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#include "func.hpp"

#include "rng.hpp"
#include <iostream>

func::func(std::size_t n) : num_var(n) {
    coeff = std::vector<double> (n+1);
    feature = std::vector<bool> (n+1);

    feature.back() = true;
}

void func::find_feature() {
    for(std::size_t i = 0; i < num_var; ++i) {
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

    return ret + coeff.back();
}

void func::show(std::ostream& out) {
    out << '(' << coeff.back() << "; " << coeff[0];
    for(size_t i = 1; i < num_var; ++i) {
        out << ", " << coeff[i];
    }
    out <<  ")";
}

void func::show_latex(std::ostream& out) {
    out << '{';

    out << coeff.back();
    for(size_t i = 0; i < num_var; ++i) {
        if (!feature[i]) continue;

        out << (coeff[i] > 0 ? '+' : '-');
        out << std::abs(coeff[i]) << "x_{" << i << '}';
    }

    out <<  '}';
}

void func::show_math(std::ostream& out) {
    out << '(';

    out << coeff.back();
    for(size_t i = 0; i < num_var; ++i) {
        if (!feature[i]) continue;

        out << (coeff[i] > 0 ? '+' : '-');
        out << std::abs(coeff[i]) << "*x" << i;
    }

    out <<  ')';
}
