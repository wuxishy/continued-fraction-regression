/**********************
 * FILE: fraction.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#ifndef __FRACTION_HPP
#define __FRACTION_HPP

// include
#include <vector>
#include "func.hpp"

class fraction {
private:
    int num_var;

public:
    fraction(int n=1) : num_var(n) {};

    double eval(std::vector<double>& vars);
    // evaluate to nth level
    double eval(std::vector<double>& vars, int n);

    std::vector<func<>> repr;
};

#endif // __FRACTION_HPP
