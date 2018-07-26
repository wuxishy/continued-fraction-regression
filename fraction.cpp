/***********************
 * FILE: fraction.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "fraction.hpp"

#include "rng.hpp"

#include <iostream>

fraction::fraction(std::size_t n) : num_var(n) {
    constant = 0;

    randint rint;

    repr = std::vector<func>(rint(2, 10));

    for (func& x : repr) x = func(num_var);
}

double fraction::eval(const std::vector<double>& vars) {
    return eval(vars, repr.size() - 1);
}

double fraction::eval(const std::vector<double>& vars, std::size_t n) {
    if (n >= repr.size()) 
        n = repr.size() - 1;
    
    // evaluating form below
    double ret = 0;
    for(int i = n; i >= 0; --i)
        ret = repr[i].eval(vars) / (1 + ret);

    return constant + ret;
}

void fraction::show(std::ostream& out) {
    out << "[" << constant;

    for(func x : repr) {
        out << ", ";
        x.show(out);
    }

    out << "]";
}
