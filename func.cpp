/**********************
 * FILE: func.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 **********************/

#include "func.hpp"

func::func(int n) : num_var(n) {
   coeff = new double[num_var]; 
}

func::~func() {
    delete[] coeff;
}
