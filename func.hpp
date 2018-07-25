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

class func {
private:
    std::size_t num_var;
    std::vector<double> coeff;

public:
    func(std::size_t n = 1);

    double eval(std::vector<double>& vars);

    // debug output
    void show(std::ostream& out);

    friend class fraction;
    friend class optimize;
    friend class population;
};

#endif //__FUNC_HPP
