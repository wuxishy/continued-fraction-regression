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
        coeff[i] = rint(0, 1)*2;
        if (coeff[i] == 0) feature[i] = false; 
    }

    alt_constant = 1;
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
    
    bool on = false;
    for(std::size_t i = 0; i < num_var; ++i) {
        ret += vars[i] * coeff[i];
        on |= feature[i];
    }

    return on ? ret : alt_constant;
}

void func::show(std::ostream& out) {
    bool on = false;
    for (size_t i = 0; i < num_var; ++i)
        on |= feature[i];

    if(on) {
        out << '(' << coeff[0];
        for(size_t i = 1; i < num_var; ++i) {
            out << ", " << coeff[i];
        }
        out <<  ")";
    }
    else out << alt_constant;
}

void func::show_latex(std::ostream& out) {
    out << '{';

    bool printed = false;
    for(size_t i = 0; i < num_var; ++i) {
        if (!feature[i]) continue;

        if (printed) {
            out << (coeff[i] > 0 ? '+' : '-');
            out << std::abs(coeff[i]) << "x_{" << i << '}';
        }
        else {
            out << coeff[i] << "x_{" << i << '}';
            printed = true;
        }
    }
    // if no feature was on
    if(!printed) out << alt_constant;

    out <<  '}';
}

void func::show_math(std::ostream& out) {
    out << '(';

    bool printed = false;
    for(size_t i = 0; i < num_var; ++i) {
        if (!feature[i]) continue;

        if (printed) {
            out << (coeff[i] > 0 ? '+' : '-');
            out << std::abs(coeff[i]) << "*x_" << i;
        }
        else {
            out << coeff[i] << "*x_" << i;
            printed = true;
        }
    }
    // if no feature was on
    if(!printed) out << alt_constant;

    out <<  ')';
}
