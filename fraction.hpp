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

    double eval(const std::vector<double>& vars);
    // evaluate to nth level
    double eval(const std::vector<double>& vars, std::size_t n);
    
    double constant;
    std::vector<func> repr;

    int num_feature();
    // debug output
    void show(std::ostream& out);
    // latex output
    void show_latex(std::ostream& out);
    // math output
    void show_math(std::ostream& out);

    friend class population;
};

#endif // __FRACTION_HPP
