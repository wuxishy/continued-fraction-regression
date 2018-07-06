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
    std::size_t num_var;

public:
    fraction(std::size_t n=1);

    double eval(std::vector<double>& vars);
    // evaluate to nth level
    double eval(std::vector<double>& vars, std::size_t n);

    std::vector<func> repr;
};

#endif // __FRACTION_HPP
