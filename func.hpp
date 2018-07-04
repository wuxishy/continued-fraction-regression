/**********************
 * FILE: func.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#ifndef __FUNC_HPP
#define __FUNC_HPP

#include <vector>

class func {
private:
    int num_var;
    std::vector<double> coeff;

public:
    func(int n = 1);

    double eval(std::vector<double>& vars);

    friend class fraction;
};

#endif //__FUNC_HPP
