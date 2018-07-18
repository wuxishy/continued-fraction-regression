/**********************
 * FILE: func.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#ifndef __FUNC_HPP
#define __FUNC_HPP

#include <vector>
#include <string>

class func {
private:
    std::size_t num_var;
    std::vector<double> coeff;

public:
    func(std::size_t n = 1);

    double eval(std::vector<double>& vars);

    std::string show();

    friend class fraction;
    friend class population;
};

#endif //__FUNC_HPP
