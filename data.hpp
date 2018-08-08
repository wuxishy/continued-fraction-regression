/**********************
 * FILE: data.hpp
 * AUTHOR: Haoyuan Sun
 * Date: July, 2018
 **********************/

// abstraction over the test data
// TODO: cache fraction evaluation

#ifndef __DATA_STORE_HPP
#define __DATA_STORE_HPP

// forward declare
class fraction;
#include <iosfwd>

// include
#include <vector>
using std::vector;
using std::size_t;

struct data_store {
    int num_entry;
    int num_var;
    vector<double> expected;
    vector<vector<double>> input;

    void read(const char* filename);

    double eval_raw_fit(fraction& frac) const;
    double eval_fit(fraction& frac) const;
    double adjust_fit(fraction& frac, double fit) const;

    // debugging purpose, only works for one variable
    void print_val(const char* filename, fraction& frac);
};

#endif // __DATA_STORE_HPP
