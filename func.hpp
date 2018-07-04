/**********************
 * FILE: func.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#ifndef __FUNC_HPP
#define __FUNC_HPP

class func {
private:
    int num_var;
    double* coeff;

public:
    func(int n);
    ~func();

    friend class fraction;
};

#endif //__FUNC_HPP
