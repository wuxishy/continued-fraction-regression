/**********************
 * FILE: func.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#include "func.hpp"

template <typename T>
func<T>::func(int n) : num_var(n) {
   coeff = std::vector<T> (n); 
}

template<typename T>
double func<T>::eval(std::vector<double>& vars) {
    double ret = 0;
    for(int i = 0; i < num_var; ++i) {
        ret += vars[i] * coeff[i];
    }

    return ret;
}
