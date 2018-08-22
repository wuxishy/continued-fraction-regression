/***********************
 * FILE: optimize.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#ifndef __OPTIMIZE_HPP__
#define __OPTIMIZE_HPP__

// forward declare
class data_store;
class evaluator;
class fraction;

// include
#include <vector>
using std::vector;
using std::size_t;

class optimize {
private:
    const data_store& test_data;

    fraction& frac;

    using pii = std::pair<int, int>;
    int ndim;
    vector<pii> var_map;

    double eval_fit (const vector<double>& vec, fraction& buf,
            const evaluator& e) const;
    double nelder_mead (fraction& frac, const evaluator& e) const;

public:
    optimize(data_store& td, fraction& f);

    double run (int type);
};
#endif // __OPTIMIZE_HPP__
