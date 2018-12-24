/**********************
 * FILE: func.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#ifndef __FUNC_HPP
#define __FUNC_HPP

// forward declare
#include <iosfwd>

// include
#include <vector>
using std::vector;
using std::size_t;

class func {
public:
//private:
    size_t num_var;
    vector<bool> feature;
    vector<double> coeff;

    void find_feature();

//public:
    static constexpr double eps = 0.001;

    func(std::size_t n = 1);

    double eval(const vector<double>& vars);

    // debug output
    void show(std::ostream& out);
    // latex output
    void show_latex(std::ostream& out);
    // math output
    void show_math(std::ostream& out);

    friend class fraction;
    friend class optimize;
    friend class population;
};

#endif //__FUNC_HPP
