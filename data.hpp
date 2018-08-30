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
#include <iosfwd>

// include
#include <vector>
using std::vector;
using std::size_t;

#include <unordered_map>

struct data_store {
    int num_entry;
    int num_var;
    vector<double> expected;
    vector<vector<double>> input;

    std::unordered_map<int, int> count;
    void make_count();

    void read(const char* filename);
};

#endif // __DATA_STORE_HPP
