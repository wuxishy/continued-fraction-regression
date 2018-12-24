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
using std::vector;
using std::size_t;

#include "func.hpp"

class fraction {
private:
    size_t num_var;

public:
    size_t depth;
    vector<bool> feature;
    vector<func> repr;
    
    fraction(std::size_t n=1);

    double eval(const vector<double>& vars);
    // evaluate to nth level
    double eval(const vector<double>& vars, size_t n);

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
