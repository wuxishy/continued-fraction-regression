/***********************
 * FILE: fraction.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "fraction.hpp"

fraction::fraction(std::size_t n) : num_var(n) {
    repr = std::vector<func>(2);
}

double fraction::eval(std::vector<double>& vars) {
    return eval(vars, repr.size() - 1);
}

double fraction::eval(std::vector<double>& vars, std::size_t n) {
    if (n >= repr.size()) 
        n = repr.size() - 1;

    double ret = 0;
    for(int i = n; i >= 1; --i)
        ret = repr[i].eval(vars) / (1 + ret);

    return ret + repr[0].eval(vars);
}
