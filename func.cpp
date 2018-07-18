/**********************
 * FILE: func.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#include "func.hpp"

#include "rng.hpp"

#include <sstream>
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

std::string func::show() {
    std::stringstream ss;
    ss.precision(2);
    
    ss << coeff[0];
    std::string ret = "(" + ss.str();
    ss.str("");
    
    for(std::size_t i = 1; i < num_var; ++i) {
        ss << coeff[i];
        ret += ", " + ss.str();
        ss.str("");
    }

    return ret + ")";
}
