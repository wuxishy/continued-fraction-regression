/***********************
 * FILE: evolve.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "gp.hpp"
#include "agent.hpp"

#include <cmath>
#include "rng.hpp"

void population::eval_fit(agent* a, int i) {
    a->fitness[i] = a->member[i].eval_fit(num_entry, expected, data);
}

void population::recombine(agent* a, agent* b) {
    
    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}

void population::mutate(agent* a) {
    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}
