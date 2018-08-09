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

fraction::fraction(std::size_t n) : num_var(n) {
    constant = 0;

    randint rint;

    repr = std::vector<func>(rint(7, 10));

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

    if(!std::isfinite(ret)) {
	for(double x : vars) std::cout << x << ' ';
	std::cout << '\n';
        show_math(std::cout);
	std::cout << '\n';
	show_latex(std::cout);
	std::cout << '\n';
	
	ret = 0;
	for(int i = n; i >= 0; --i) {
	    ret = repr[i].eval(vars) / (1 + ret);
	    std::cout << ret << ' ';
	}
	std::cout << '\n';

	// assert(false);
    }

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
    out << "[" << constant;

    for(func x : repr) {
        out << ", ";
        x.show(out);
    }

    out << "]";
}

void fraction::show_latex(std::ostream& out) {
    out << '$' << constant << '+';
    
    for(std::size_t i = 0; i < repr.size(); ++i) {
        if (i == repr.size() - 1) {
            repr[i].show_latex(out);
        }
        else {
            out << "\\cfrac{";
            repr[i].show_latex(out);
            out << "}{1+";
        }
    }
    
    for(std::size_t i = 0; i < repr.size()-1; ++i)
        out << '}';

    out << '$';
}

void fraction::show_math(std::ostream& out) {
    out << constant << '+';
    
    for(std::size_t i = 0; i < repr.size(); ++i) {
        if (i == repr.size() - 1) {
            repr[i].show_math(out);
        }
        else {
            repr[i].show_math(out);
            out << "/(1+";
        }
    }
    
    for(std::size_t i = 0; i < repr.size()-1; ++i)
        out << ')';
}
