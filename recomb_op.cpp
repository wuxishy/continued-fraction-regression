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
    int ind = rint(1, std::min(a->member[1].repr.size(), 
                b->member[1].repr.size())) - 1;
    
    vector<double>& acoeff = a->member[1].repr[ind].coeff;
    vector<double>& bcoeff = b->member[1].repr[ind].coeff;
    
    // find the shared varaiables
    int ndim = 0;
    vector<bool> vdim(test_data.num_var, false);
    for(int i = 0; i < test_data.num_var; ++i) {
        if (std::abs(acoeff[i]) > eps && std::abs(bcoeff[i]) > eps) {
            vdim[i] = true;
            ++ndim;
        }
    }

    optimize opt(test_data);
    opt.set_dim(ndim, vdim);

    opt.run(1, a->member[1], acoeff);
   
    // set anything small to simply 0
    for(int i = 0; i < test_data.num_var; ++i) {
        if (std::abs(acoeff[i]) < eps) 
            acoeff[i] = 0;
    }
}

void population::exchange_branch(agent* a, agent* b) {
    int ind = rint(1, std::min(a->member[1].repr.size(), 
                b->member[1].repr.size())) - 1;

    a->member[1].repr.resize(ind);

    for(size_t i = ind; i < b->member[1].repr.size(); ++i)
        a->member[1].repr.push_back(b->member[1].repr[i]);
    
    // optimize at where the fractions joined
    vector<double>& acoeff = a->member[1].repr[ind].coeff;
    
    // find the shared varaiables
    int ndim = 0;
    vector<bool> vdim(test_data.num_var, false);
    for(int i = 0; i < test_data.num_var; ++i) {
        if (std::abs(acoeff[i]) > eps) {
            vdim[i] = true;
            ++ndim;
        }
    }

    optimize opt(test_data);
    opt.set_dim(ndim, vdim);

    opt.run(1, a->member[1], acoeff);
   
    // set anything small to simply 0
    for(int i = 0; i < test_data.num_var; ++i) {
        if (std::abs(acoeff[i]) < eps) 
            acoeff[i] = 0;
    }
}

