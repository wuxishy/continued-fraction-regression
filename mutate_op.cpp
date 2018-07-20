/***********************
 * FILE: mutate_op.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "gp.hpp"

#include "optimize.hpp"

#include "agent.hpp"
#include "fraction.hpp"
#include "func.hpp"

// point mutation
void population::leader_mutate(agent* a) {
    // mutate only if current is a lot worse
    // than leader
    //if (a->fitness[0] > a->fitness[1]/2)
    //    return;

    a->member[1] = a->member[0];
    int ind = rint(1, a->member[1].repr.size()) - 1;
    a->member[1].repr[ind] = func();
    
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
