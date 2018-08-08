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
#include <numeric>
#include <algorithm>

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

double data_store::eval_raw_fit(fraction& frac) const { 
    double ret = 0;

    auto sqr = [] (double x) -> double { return x*x; };
    
    #pragma omp parallel for reduction(+:ret)
    for(int i = 0; i < num_entry; ++i) {
        ret += sqr(expected[i] - frac.eval(input[i]));
    }
   
    return ret / num_entry;
}

double data_store::eval_fit(fraction& frac) const {
    double* arr = new double[num_entry];

    #pragma omp parallel for
    for(int i = 0; i < num_entry; ++i) {
        arr[i] = std::abs(expected[i] - frac.eval(input[i]));
    }

    int q1 = num_entry/4, q3 = 3*num_entry/4;
    std::sort(arr, arr+num_entry);

    double ret = std::accumulate(arr+q1, arr+q3+1, 0.0);

    delete[] arr;

    return ret / (q3-q1+1);
}

double data_store::adjust_fit(fraction& frac, double fit) const {
    double factor = std::max(1.0, 1 + (frac.num_feature()-3) * 0.5);

    return factor * fit;
}

void data_store::print_val(const char* filename, fraction& frac) {
    std::ofstream fout(filename);
    
    for(int i = 0; i < num_entry; ++i)
        fout << expected[i] << ',' << frac.eval(input[i]) << '\n';

    fout.close();
}
