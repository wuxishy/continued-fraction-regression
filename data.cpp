/******************************
 * FILE: data.cpp
 * AUTHOR: Haoyuan Sun
 * Date: July, 2018
 ******************************/

#include "data.hpp"
#include "fraction.hpp"

#include <fstream>
#include <sstream>
#include <string>

#include <cmath>

#include <cassert>

void data_store::read(const char* filename) {
    std::ifstream fin(filename);
   
    fin >> num_entry >> num_var;
    fin.ignore();

    std::string line;
    for(int i = 0; i < num_entry; ++i) {
        std::getline(fin, line);
        
        double tmp;
        std::istringstream tokenizer(line);

        tokenizer >> tmp;
        expected.push_back(tmp);

        input.push_back(vector<double>());
        
        for (int j = 0; j < num_var; ++j) {
            tokenizer >> tmp;
            input.back().push_back(tmp);
        }

    }

    fin.close();
}

double data_store::eval_fit(fraction& frac) const { 
    double ret = 0;

    auto sqr = [] (double x) -> double { return x*x; };
    
    for(int i = 0; i < num_entry; ++i) {
        ret += sqr(expected[i] - frac.eval(input[i]));
    }
    
    return ret / num_entry;
}

void data_store::print_val(const char* filename, fraction& frac) {
    std::ofstream fout(filename);
    
    for(int i = 0; i < num_entry; ++i)
        fout << expected[i] << ',' << frac.eval(input[i]) << std::endl;

    fout.close();
}
