/***********************
 * FILE: evolve.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

// basic features of evolution

#include "gp.hpp"
#include "agent.hpp"
#include "optimize.hpp"

#include <cmath>
#include "rng.hpp"
#include "comp.hpp"

#include <cassert>
#include <iostream> 

void population::eval_fit(agent* a, int i) {
    a->fitness[i] = test_data.adjust_fit(a->member[i], 
            test_data.eval_fit(a->member[i]));
}

void population::recombine(agent* a, agent* b) {
    //double tmp = a->fitness[1];

    switch(rint(1, 5)) {
        case 1:
            exchange_branch(a, b);
            break;
        case 2:
            variable_union(a, b);
            break;
        default:
            variable_intersect(a, b);
            break;
    }

    eval_fit(a, 1);
/*
    if (a->fitness[1] < tmp || a->fitness[1] < b->fitness[1])
        std::cerr << "Rich!" << std::endl;
    else
        std::cerr << "Poor!" << std::endl;
*/
    a->update_pocket();
    a->propagate_pocket();
}

void population::mutate(agent* a) {
    if(rint(1, 5) == 1) {
        // a rather major mutation
        // only mutate if current is too close or much worse
        // that pocket
        if (comp_less()(a->fitness[1], 1.2 * a->fitness[0]) || 
                comp_greater()(a->fitness[1], 2 * a->fitness[0]))
            feature_toggle(a->member[1]);
        // or we perturb only slightly
        else expand_feature(a->member[1]);
    }

    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}

void population::local_search(agent* a) {
    if (a->depth > 1) {
        for(std::size_t i = 0; i < a->degree; ++i)
            local_search(a->children[i]);
    }
    
    optimize opt(test_data, a->member[1]);
    a->fitness[1] = opt.run(1);

    if (comp_greater()(a->fitness[0], a->fitness[1])) {
        optimize more_opt(test_data, a->member[0]);
        a->fitness[0] = more_opt.run(1);
    }

    a->movedown_pocket();
}

void population::diversify(agent* a) {
    if (a->depth > 1) {
        for(std::size_t i = 0; i < a->degree; ++i)
            diversify(a->children[i]);
    }

    // kill the pocket if too close to parent
    if (a->parent) {
        if (comp_less()(a->fitness[0], 1.01 * a->parent->fitness[0]) &&
                // also add a coin toss
                rint(1, 2) == 1) {

            a->member[0] = fraction(test_data.num_var);
            eval_fit(a, 0);
        }
    }
    a->movedown_pocket();
}

void population::simplify(agent* a) {
    if (a->depth > 1) {
        for(std::size_t i = 0; i < a->degree; ++i)
            simplify(a->children[i]);
    }
    
    fraction& frac = a->member[1];
    
    int total = 0;
    vector<int> occur(test_data.num_var, 0);
    
    for(func& f : frac.repr)
        for(int i = 0; i < test_data.num_var; ++i) {
            occur[i] += f.feature[i];
            total += f.feature[i];
        }

    int num_feature = 0;
    for(int x : occur) num_feature += (x > 0);
    // do not touch if number of features is already small
    if (num_feature <= 2 || num_feature <= 0.1 * test_data.num_var)
        return;

    // randomly kill off less common feature
    for(int i = 0; i < test_data.num_var; ++i) {
        // do not touch those common ones
        if (occur[i] * test_data.num_var >= 2 * total) continue;

        // less common -> more likely to die
        if (rint(1, total) > occur[i]) {
            for (func& f : frac.repr) {
                f.feature[i] = false;
                f.coeff[i] = 0;
            }
        }
    }

    eval_fit(a, 1);

    a->movedown_pocket();
}
