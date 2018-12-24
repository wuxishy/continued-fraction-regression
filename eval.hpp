/**********************
 * FILE: eval.hpp
 * AUTHOR: Haoyuan Sun
 * Date: August, 2018
 * ********************/

#ifndef __EVAL_HPP
#define __EVAL_HPP

class data_store;
class fraction;

#include <unordered_set>

class evaluator {
private:
    const data_store& data;
    std::unordered_set<int> selection;

public:
    evaluator(const data_store& td);
    evaluator(const data_store& td, int num);

    double eval_fit(fraction& frac) const;
    double eval_fit_full(fraction& frac) const;
    double adjust_fit(fraction& frac, double fit) const;

    void print_val(const char* filename, fraction& frac) const;
};

#endif // __EVAL_HPP
