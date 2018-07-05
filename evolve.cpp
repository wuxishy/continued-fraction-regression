/***********************
 * FILE: evolve.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "gp.hpp"
#include "agent.hpp"
#include <cmath>

void population::eval_fit(agent* a) {
    a->fitness[1] = 0;

    for(int i = 0; i < num_entry; ++i) {
        a->fitness[1] += abs(expected[i] - a->member[0].eval(data[i]));
    } 
}

void population::recombine(agent* a, agent* b) {
    eval_fit(a);

    a->update_pocket();
    a->propagate_pocket();
}

void population::mutate(agent* a) {
    eval_fit(a);

    a->update_pocket();
    a->propagate_pocket();
}
