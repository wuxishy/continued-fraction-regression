/***********************
 * FILE: evolve.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

// basic features of evolution

#include "gp.hpp"
#include "agent.hpp"

#include <cmath>
#include "rng.hpp"

#include <iostream> 

void population::eval_fit(agent* a, int i) {
    a->fitness[i] = test_data.eval_fit(a->member[i]);
}

void population::recombine(agent* a, agent* b) {
    double tmp = a->fitness[1];

    switch(rint(2, 3)) {
        case 1:
            exchange_branch(a, b);
            break;
        case 2:
            variable_intersect(a, b);
            break;
        case 3:
            variable_union(a, b);
            break;
    }

    eval_fit(a, 1);

    if (a->fitness[1] < tmp || a->fitness[1] < b->fitness[1])
        std::cerr << "Rich!" << std::endl;
    else
        std::cerr << "Poor!" << std::endl;

    a->update_pocket();
    a->propagate_pocket();
}

void population::mutate(agent* a) {
    return;

    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}
