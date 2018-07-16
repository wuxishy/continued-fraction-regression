/***********************
 * FILE: recomb_op.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "gp.hpp"

#include "optimize.hpp"

#include "agent.hpp"
#include "fraction.hpp"
#include "func.hpp"

void population::variable_intersect(agent* a, agent* b) {
    optimize opt(num_entry, expected, data);

    int ind = rint(1, std::min(a->member[1].repr.size(), 
                b->member[1].repr.size())) - 1;
    
    vector<double>& acoeff = a->member[1].repr[ind].coeff;
    vector<double>& bcoeff = b->member[1].repr[ind].coeff;
    
    constexpr double eps = 0.001;

    // find the shared varaiables
    int ndim = 0;
    vector<bool> vdim(num_var, false);
    for(size_t i = 0; i < num_var; ++i) {
        if (std::abs(acoeff[i]) > eps && std::abs(bcoeff[i]) > eps) {
            vdim[i] = true;
            ++ndim;
        }
    }

    opt.set_dim(ndim, vdim);

    opt.run(1, a->member[1], acoeff);
   
    // set anything small to simply 0
    for(size_t i = 0; i < num_var; ++i) {
        if (std::abs(acoeff[i]) < eps) 
            acoeff[i] = 0;
    }
}

void population::leader_mutate(agent* a) {
    // mutate only if current is a lot worse
    // than leader
    if (a->fitness[0] > a->fitness[1]/2)
        return;

    a->member[1] = a->member[0];
    int n = rint(0, 1);
    a->member[1].repr[n] = func();
}
