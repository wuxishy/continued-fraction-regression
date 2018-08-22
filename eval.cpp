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

#include <cmath>

#include <cassert>

evaluator::evaluator(const data_store& td) : test_data(td) {
    arr = vector<int>();
}

evaluator::evaluator(const data_store& td, int num) : test_data(td) {
    arr = vector<int>();
    
    randint rint;
    for (int i = 0; i < num; ++i) {
        arr.push_back(rint(0, test_data.num_entry-1));
    }
}

double evaluator::eval_fit(fraction& frac) const { 
    if (arr.empty()) return eval_fit_full(frac);
    
    double ret = 0;

    auto sqr = [] (double x) -> double { return x*x; };
    
    for(int i : arr) {
        ret += sqr(test_data.expected[i] - 
                frac.eval(test_data.input[i]));
    }
   
    if (std::isfinite(ret)) return ret / test_data.num_entry;
    else return INFINITY;
}

double evaluator::eval_fit_full(fraction& frac) const { 
    double ret = 0;

    auto sqr = [] (double x) -> double { return x*x; };
    
    for(int i = 0; i < test_data.num_entry; ++i) {
        ret += sqr(test_data.expected[i] - 
                frac.eval(test_data.input[i]));
    }
   
    if (std::isfinite(ret)) return ret / test_data.num_entry;
    else return INFINITY;
}

double evaluator::adjust_fit(fraction& frac, double fit) const {
    if (!std::isfinite(fit)) return INFINITY;

    double factor = std::max(1.0, 1 + (frac.num_feature()-3) * 0.5);

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
