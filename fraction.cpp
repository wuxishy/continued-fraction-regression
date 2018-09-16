/***********************
 * FILE: fraction.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "fraction.hpp"

#include "rng.hpp"

#include <iostream>

#include <cassert>
#include <cmath>

fraction::fraction(size_t n) : num_var(n) {
    randint rint;

    depth = 5;

    constant = 0;
    const_feature = vector<bool>(depth);

    feature = vector<bool>(num_var);
    repr = vector<func>(depth);

    for (size_t i = 0; i < num_var; ++i) 
        feature[i] = (rint(0, 4) ? false : true);

    for(size_t i = 0; i < depth; ++i) {
        const_feature[i] = rint(0, 1);

        repr[i] = func(num_var);
        for (size_t j = 0; j < num_var; ++j) {
            if (!feature[j]) continue;

            repr[i].coeff[j] = rint(-3, 3);
            if (repr[i].coeff[j] != 0) 
                repr[i].feature[j] = true; 
        }
        repr[i].alt_constant = rint(-3, 3);
    }
}

double fraction::eval(const vector<double>& vars) {
    return eval(vars, repr.size() - 1);
}

double fraction::eval(const vector<double>& vars, size_t n) {
    if (n >= repr.size()) 
        n = repr.size() - 1;
    
    // evaluating form below
    double ret = repr[n].eval(vars);
    for(int i = n-1; i >= 0; --i)
        ret = repr[i].eval(vars) / (const_feature[i+1] + ret);

    return constant + ret;
}

int fraction::num_feature() {
    int ret = 0;
    for(bool x : feature) ret += x;

    return ret;
}

void fraction::show(std::ostream& out) {
    out << "[";

    for(size_t i = 0; i < depth; ++i) {
        if (i > 0) out << "; ";
        out << (i ? const_feature[i] : constant) << ", ";
        repr[i].show(out);
    }

    out << "]";
}

void fraction::show_latex(std::ostream& out) {
    out << '$';
    
    for(size_t i = 0; i < depth; ++i) {
        if (i == 0) out << constant << '+';
        else if (const_feature[i]) out << "1+";

        if (i == depth-1)
            repr[i].show_latex(out);
        else {
            out << "\\cfrac{";
            repr[i].show_latex(out);
            out << "}{";
        }
    }
    
    for(size_t i = 0; i < depth-1; ++i)
        out << '}';

    out << '$';
}

void fraction::show_math(std::ostream& out) {
    for(size_t i = 0; i < depth; ++i) {
        if (i == 0) out << constant << '+';
        else if (const_feature[i]) out << "1+";

        if (i == depth-1)
            repr[i].show_math(out);
        else {
            repr[i].show_math(out);
            out << "/(";
        }
    }
    
    for(size_t i = 0; i < depth-1; ++i)
        out << ')';
}
