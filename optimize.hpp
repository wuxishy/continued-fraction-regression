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
#include <vector>
using std::vector;
using std::size_t;

class optimize {
private:
    int num_entry;
    vector<double>& expected;
    vector<vector<double>>& data;

    int ndim;
    vector<bool> vdim;

    double eval_fit (fraction& frac, vector<double>& coeff, 
    	const vector<double>& var);
    void nelder_mead (fraction& frac, vector<double>& coeff);

public:
    optimize(int n, vector<double>& e, vector<vector<double>>& d);

    void set_dim (int n, const vector<bool>& v);

    void run (int type, fraction& frac, vector<double>& coeff);
};
#endif // __OPTIMIZE_HPP__
