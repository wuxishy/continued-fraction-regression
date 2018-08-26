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
    const_feature = vector<bool>(depth);
    repr = vector<func>(depth);

    constant = 0;

    for(size_t i = 0; i < depth; ++i) {
        repr[i] = func(num_var);
        const_feature[i] = rint(0, 1);
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
