/******************************
 * FILE: data.cpp
 * AUTHOR: Haoyuan Sun
 * Date: July, 2018
 ******************************/

#include "data.hpp"

#include <fstream>
#include <string>

#include <cmath>

#include <cassert>

void data_store::make_count() {
    for (double x : expected) {
    	int tmp = std::lround(x);
	auto it = count.find(tmp);
	if (it == count.end()) count.insert({tmp, 1});
	else ++(it->second);
    }
}

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
