/***********************
 * FILE: optimize.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#ifndef __OPTIMIZE_HPP__
#define __OPTIMIZE_HPP__

// forward declare
class fraction;
class func;

// include
#include "data.hpp"

#include <vector>
using std::vector;
using std::size_t;

class optimize {
private:
    data_store& test_data;
    int ndim;
    vector<bool> vdim;

    double eval_fit (fraction& frac, vector<double>& coeff, 
    	const vector<double>& var);
    void nelder_mead (fraction& frac, vector<double>& coeff);

public:
    optimize(data_store& td);

    void set_dim (int n, const vector<bool>& v);

    void run (int type, fraction& frac, vector<double>& coeff);
};
#endif // __OPTIMIZE_HPP__
