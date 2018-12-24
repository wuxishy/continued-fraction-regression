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

    depth = 3;

    feature = vector<bool>(num_var);
    repr = vector<func>(depth*2+1);

    for (size_t i = 0; i < num_var; ++i) 
        feature[i] = (rint(0, 2) ? false : true);

    for(size_t i = 0; i < depth*2+1; ++i) {
        repr[i] = func(num_var);
        for (size_t j = 0; j < num_var; ++j) {
            if (!feature[j]) continue;

            repr[i].coeff[j] = rint(-3, 3);
            if (repr[i].coeff[j] != 0) 
                repr[i].feature[j] = true; 
        }
        repr[i].coeff[num_var] = rint(-3, 3);
        repr[i].feature[num_var] = true;
    }
}

double fraction::eval(const vector<double>& vars) {
    return eval(vars, depth);
}

double fraction::eval(const vector<double>& vars, size_t n) {
    if (n > depth) n = depth;
    
    // evaluating form below
    double ret = repr[2*n].eval(vars);
    for(int i = n-1; i >= 0; --i)
        ret = repr[i*2].eval(vars) + (repr[2*i+1].eval(vars) / ret);

    return ret;
}

int fraction::num_feature() {
    std::vector<bool> occur(num_var, false);
    for (func& f : repr)
        for(std::size_t i = 0; i < num_var; ++i)
            occur[i] = occur[i] | f.feature[i];

    int ret = 0;
    for(bool x : occur) ret += x;

    return ret;
}

void fraction::show(std::ostream& out) {
    out << "[";

    for(size_t i = 0; i <= depth; ++i) {
        repr[2*i].show(out);
        if (i != depth) {
            out << ", ";
            repr[2*i+1].show(out);
            out << "; ";
        }
    }

    out << "]";
}

void fraction::show_latex(std::ostream& out) {
    out << '$';
    
    repr[0].show_latex(out);
    out << '+';
    for(size_t i = 1; i <= depth; ++i) {
        out << "\\cfrac{";
        repr[2*i-1].show_latex(out);
        out << "}{";
        repr[2*i].show_latex(out);
        if (i != depth) out << '+';
    }
    
    for(size_t i = 1; i <= depth; ++i)
        out << '}';

    out << '$';
}

void fraction::show_math(std::ostream& out) {
    repr[0].show_math(out);
    out << '+';
    for(size_t i = 1; i <= depth; ++i) {
        repr[2*i-1].show_math(out);
        out << "/(";
        repr[2*i].show_math(out);
        if (i != depth) out << '+';
    }
    
    for(size_t i = 1; i <= depth; ++i)
        out << ')';
}
