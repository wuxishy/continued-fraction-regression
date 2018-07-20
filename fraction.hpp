/**********************
 * FILE: fraction.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

// continued fraction representation

#ifndef __FRACTION_HPP
#define __FRACTION_HPP

// forward declare
#include <iosfwd>

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
    
    double constant;
    std::vector<func> repr;

    // debug output
    void show(std::ostream& out);
};

#endif // __FRACTION_HPP
