/******************************
 * FILE: data.cpp
 * AUTHOR: Haoyuan Sun
 * Date: July, 2018
 ******************************/

#include "data.hpp"
#include "fraction.hpp"

#include <fstream>
#include <string>

#include <cmath>
#include "omp.h"

#include <cassert>

void data_store::read(const char* filename) {
    std::ifstream fin(filename);
   
    fin >> num_entry >> num_var;

    std::string line;
    for(int i = 0; i < num_entry; ++i) {
        double tmp;

        fin >> tmp;
        expected.push_back(tmp);

        input.push_back(vector<double>());
        
        for (int j = 0; j < num_var; ++j) {
            fin >> tmp;
            input.back().push_back(tmp);
        }

    }

    fin.close();
}

data_store data_store::gen_error(fraction& frac) {
    data_store next;
    next.num_entry = this->num_entry;
    next.num_var = this->num_var;
    next.input = this->input;

    next.expected = vector<double>(0);
    for (int i = 0; i < num_entry; ++i)
        next.expected.push_back(expected[i] - frac.eval(input[i]));

    return next;
}

double data_store::eval_fit(fraction& frac) const { 
    double ret = 0;
    
    #pragma omp parallel for reduction(+:ret)
    for(int i = 0; i < num_entry; ++i) {
        ret += std::abs(expected[i] - frac.eval(input[i]));
    }
   
    if (std::isfinite(ret)) return ret / num_entry;
    else return INFINITY;
}

double data_store::adjust_fit(fraction& frac, double fit) const {
    if (!std::isfinite(fit)) return INFINITY;

    double factor = std::max(1.0, 1 + (frac.num_feature()-3) * 0.5);

    return factor * fit;
}

void data_store::print_val(const char* filename, fraction& frac) {
    std::ofstream fout(filename);
    
    for(int i = 0; i < num_entry; ++i)
        fout << expected[i] << ',' << frac.eval(input[i]) << '\n';

    fout.close();
}
