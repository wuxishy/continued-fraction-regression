/***********************
 * FILE: fraction.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "fraction.hpp"

#include "rng.hpp"

fraction::fraction(std::size_t n) : num_var(n) {
    randint rint;

    repr = std::vector<func>(rint(2, 10));

    for (func& x : repr) x = func(num_var);
}

double fraction::eval(std::vector<double>& vars) {
    return eval(vars, repr.size() - 1);
}

double fraction::eval(std::vector<double>& vars, std::size_t n) {
    if (n >= repr.size()) 
        n = repr.size() - 1;

    double ret = 0;
    for(int i = n; i >= 0; --i)
        ret = repr[i].eval(vars) / (1 + ret);

    return constant + ret;
}

std::string fraction::show() {
    std::string ret = "[" + std::to_string(constant);

    for(func x : repr) ret += ", " + x.show();

    return ret + "]";
}
