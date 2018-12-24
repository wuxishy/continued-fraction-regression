/***********************
 * FILE: evolve.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

// basic features of evolution

#include "gp.hpp"
#include "agent.hpp"
#include "optimize.hpp"

#include "eval.hpp"

#include <cmath>
#include "rng.hpp"

#include <cassert>
#include <iostream> 

void population::eval_fit(agent* a, int i) {
    a->fitness[i] = train_e.adjust_fit(a->member[i], 
            train_e.eval_fit(a->member[i]));
}

void population::recombine(agent* a, agent* b) {
    switch(rint(1, 3)) {
        case 1:
            variable_intersect(a, b);
            break;
        case 2:
            variable_union(a, b);
            break;
        case 3:
            variable_symdiff(a, b);
        default:
            break;
    }

    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}

void population::mutate(agent* a) {
    if(rint(1, 4) == 1) {
        // a rather major mutation
        // only mutate if current is too close or much worse
        // that pocket
        if (a->fitness[1] < 1.2 * a->fitness[0] || 
                a->fitness[1] > 2 * a->fitness[0])
            feature_toggle(a->member[1]);
        // or we perturb only slightly
        else feature_mod(a->member[1]);
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
    
    optimize opt(train_data, a->member[1]);
    a->fitness[1] = opt.run();

    if (a->fitness[0] > a->fitness[1]) {
        optimize more_opt(train_data, a->member[0]);
        a->fitness[0] = more_opt.run();
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
        if (a->fitness[0] < 1.01 * a->parent->fitness[0] &&
                // also add a coin toss
                rint(1, 2) == 1) {

            a->member[0] = fraction(num_var);
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
    vector<int> occur(num_var, 0);
    
    for(func& f : frac.repr)
        for(int i = 0; i < num_var; ++i) {
            occur[i] += f.feature[i];
            total += f.feature[i];
        }

    int num_feature = 0;
    for(int x : occur) num_feature += (x > 0);
    // do not touch if number of features is already small
    if (num_feature <= 2 || num_feature <= 0.1 * num_var)
        return;

    // randomly kill off less common feature
    for(int i = 0; i < num_var; ++i) {
        // do not touch those common ones
        if (occur[i] * num_var >= 2 * total) continue;

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
