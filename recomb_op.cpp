/***********************
 * FILE: recomb_op.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

// recombination operations

#include "gp.hpp"

#include "optimize.hpp"

#include "agent.hpp"
#include "fraction.hpp"
#include "func.hpp"

void population::variable_intersect(agent* a, agent* b) {
    int ind = rint(1, std::min(a->member[0].repr.size(), 
        std::min(a->member[1].repr.size(), b->member[1].repr.size()))) - 1;
    
    vector<double>& acoeff = a->member[0].repr[ind].coeff;
    vector<bool>& afeature = a->member[0].repr[ind].feature;
    vector<double>& bcoeff = b->member[1].repr[ind].coeff;
    vector<bool>& bfeature = b->member[1].repr[ind].feature;
    
    // find the shared varaiables
    vector<double> new_coeff(test_data.num_var);
    for(int i = 0; i < test_data.num_var; ++i) {
        if (afeature[i] && bfeature[i]) {
            // six equally spaced points around the parents
            new_coeff[i] = acoeff[i] + rint(-1, 4) * (bcoeff[i] - acoeff[i]) / 3;
        }
    }

    a->member[1].repr[ind].coeff = new_coeff;
    a->member[1].repr[ind].find_feature();
}

void population::variable_union(agent* a, agent* b) {
    int ind = rint(1, std::min(a->member[0].repr.size(), 
        std::min(a->member[1].repr.size(), b->member[1].repr.size()))) - 1;
    
    vector<double>& acoeff = a->member[0].repr[ind].coeff;
    vector<bool>& afeature = a->member[0].repr[ind].feature;
    vector<double>& bcoeff = b->member[1].repr[ind].coeff;
    vector<bool>& bfeature = b->member[1].repr[ind].feature;
    
    // find the shared varaiables
    vector<double> new_coeff(test_data.num_var);
    for(int i = 0; i < test_data.num_var; ++i) {
        if (afeature[i] && bfeature[i]) {
            // six equally spaced points around the parents
            new_coeff[i] = acoeff[i] + rint(-1, 4) * (bcoeff[i] - acoeff[i]) / 3;
        }
        else if (afeature[i])
            new_coeff[i] = acoeff[i];
        else if (bfeature[i])
            new_coeff[i] = bcoeff[i];
    }

    a->member[1].repr[ind].coeff = new_coeff;
    a->member[1].repr[ind].find_feature();
}

void population::exchange_branch(agent* a, agent* b) {
    int ind = rint(1, std::min(a->member[0].repr.size(), 
                b->member[1].repr.size())) - 1;

    // make a cut
    a->member[1].repr = a->member[0].repr;
    a->member[1].repr.resize(ind);

    // copy the branch from b to a;
    for(size_t i = ind; i < b->member[1].repr.size(); ++i)
        a->member[1].repr.push_back(b->member[1].repr[i]);
}

