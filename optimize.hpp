/***********************
 * FILE: optimize.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#ifndef __OPTIMIZE_HPP__
#define __OPTIMIZE_HPP__

// forward declare
class data_store;

// include
#include "fraction.hpp"

#include <vector>
using std::vector;
using std::size_t;

class optimize {
private:
    const data_store& test_data;

    fraction& frac;
    fraction buf;

    using pii = std::pair<int, int>;
    int ndim;
    vector<pii> var_map;

    double eval_fit (const vector<double>& vec);
    double nelder_mead ();

public:
    optimize(data_store& td, fraction& f);

    double run (int type);
};
#endif // __OPTIMIZE_HPP__
