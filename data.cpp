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

double data_store::eval_fit(fraction& frac) const { 
    double ret = 0;

    auto sqr = [] (double x) -> double { return x*x; };
    auto logistics = [] (double x) -> double { 
	    return 1 / (1 + std::exp(-x)); 
    };

    #pragma omp parallel for reduction(+:ret)
    for(int i = 0; i < num_entry; ++i) {
        ret += sqr(expected[i] - logistics(frac.eval(input[i])));
    }
   
    if (std::isfinite(ret)) return ret / num_entry;
    else return INFINITY;
}

double data_store::adjust_fit(fraction& frac, double fit) const {
    if (!std::isfinite(fit)) return INFINITY;

    double factor = 1;
    
    int n = frac.num_feature();
    factor += n * 0.08;
    //if (n > 10) factor += (n-10) * 2;
    if (n > 15) factor += (n-15) * 4.5;
    if (n > 50) factor += (n-50) * 23;

    return factor * fit;
}

void data_store::print_val(const char* filename, fraction& frac) {
    std::ofstream fout(filename);
    
    for(int i = 0; i < num_entry; ++i)
        fout << expected[i] << ',' << frac.eval(input[i]) << '\n';

    fout.close();
}
