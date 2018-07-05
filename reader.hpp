/******************************
 * FILE: reader.hpp
 * AUTHOR: Haoyuan Sun
 * Date: July, 2018
 ******************************/

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <vector>

#include <cassert>

void reader(const char* filename, std::vector<double>& expected,
        std::vector<std::vector<double>>& data) {
    std::ifstream fin(filename);
   
    int num_entry, num_var;
    fin >> num_entry >> num_var;
    fin.ignore();

    std::string line;
    for(int i = 0; i < num_entry; ++i) {
        std::getline(fin, line);
        
        double tmp;
        std::stringstream tokenizer(line);

        tokenizer >> tmp;
        expected.push_back(tmp);

        data.push_back(std::vector<double>());
        
        for (int j = 0; j < num_var; ++j) {
            tokenizer >> tmp;
            data.back().push_back(tmp);
        }

    }

    fin.close();
}
