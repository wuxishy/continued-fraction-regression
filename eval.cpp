/******************************
 * FILE: eval.cpp
 * AUTHOR: Haoyuan Sun
 * Date: August, 2018
 ******************************/

#include "eval.hpp"

#include "data.hpp"
#include "rng.hpp"
#include "fraction.hpp"

#include <fstream>

#include <map>
#include <cmath>

#include "omp.h"

#include <cassert>

evaluator::evaluator(const data_store& td) : test_data(td) {
    selection = std::vector<int>();
}

evaluator::evaluator(const data_store& td, int num) : test_data(td) {
    selection = std::vector<int>();
   
    // if too many being selected, might just as choose the whole
    if (num *2 >= test_data.num_entry) return;

    std::unordered_set<int> tmp;

    randint rint;
    int iter = 0; // guard against super bad RNG
    while (num > 0 && iter++ < test_data.num_entry) {
        auto result = tmp.insert(rint(0, test_data.num_entry-1));
        if (result.second) --num;
    }

    for(int i : tmp) selection.push_back(i);
}

static inline double eval_pt(const data_store& td, fraction& frac, int i) {
    auto sqr = [] (double x) -> double { return x*x; };
    double ret = sqr(td.expected[i] - frac.eval(td.input[i]));
    int c = td.count.at(std::lround(td.expected[i]));
    return ret / c / td.count.size();
}

static inline double process(double val) {
    return std::isfinite(val) ? val : INFINITY;
}

double evaluator::eval_fit(fraction& frac) const { 
    if (selection.empty()) return eval_fit_full(frac);
    
    double ret = 0;

    #pragma omp parallel for reduction(+:ret)
    for(size_t i = 0; i < selection.size(); ++i) {
        ret += eval_pt(test_data, frac, selection[i]);
    }

    return process(ret);
}

double evaluator::eval_fit_full(fraction& frac) const { 
    double ret = 0;

    #pragma omp parallel for reduction(+:ret)
    for(int i = 0; i < test_data.num_entry; ++i) {
        ret += eval_pt(test_data, frac, i);
    }

    return process(ret);
}

double evaluator::adjust_fit(fraction& frac, double fit) const {
    if (!std::isfinite(fit)) return INFINITY;

    double factor = 1 + std::max(0, frac.num_feature()-20) * 0.01;

    return factor * fit;
}

void evaluator::print_val(const char* filename, fraction& frac) const {
    std::ofstream fout(filename);
    
    for(int i = 0; i < test_data.num_entry; ++i) {
        fout << test_data.expected[i] << ',';
        fout << frac.eval(test_data.input[i]) << '\n';
    }

    fout.close();
}
