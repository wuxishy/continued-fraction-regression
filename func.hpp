/**********************
 * FILE: func.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#ifndef __FUNC_HPP
#define __FUNC_HPP

#include <vector>

template <typename T=double>
class func {
private:
    int num_var;
    std::vector<T> coeff;

public:
    func(int n);

    double eval(std::vector<double>& vars);

    friend class fraction;
};

#endif //__FUNC_HPP
