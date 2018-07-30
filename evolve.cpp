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

#include <cassert>
#include <iostream> 

void population::eval_fit(agent* a, int i) {
    a->fitness[i] = test_data.eval_fit(a->member[i]);
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
    return;

    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}

void population::local_search(agent* a) {
    optimize opt(test_data, a->member[1]);
    a->fitness[1] = opt.run(1);

    if (a->fitness[0] > a->fitness[1]) {
        optimize more_opt(test_data, a->member[0]);
        a->fitness[0] = more_opt.run(1);
    }

    a->update_pocket();
    a->propagate_pocket();
    
    assert(check(root));

    if (a->depth > 1) {
        for(std::size_t i = 0; i < a->degree; ++i)
            local_search(a->children[i]);
    }
}
