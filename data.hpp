/**********************
 * FILE: data.hpp
 * AUTHOR: Haoyuan Sun
 * Date: July, 2018
 **********************/

#ifndef __DATA_STORE_HPP
#define __DATA_STORE_HPP

class fraction;

#include <vector>

using std::vector;
using std::size_t;

struct data_store {
    int num_entry;
    int num_var;
    vector<double> expected;
    vector<vector<double>> input;

    void read(const char* filename);

    double eval_fit(fraction& frac);
};

#endif // __DATA_STORE_HPP
