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
    a->fitness[i] = 0;

    for(std::size_t j = 0; j < num_entry; ++j) {
        a->fitness[i] += abs(expected[j] - a->member[i].eval(data[j]));
    } 
}

void population::recombine(agent* a, agent* b) {
    // just random stuff for now
    a->member[1] = a->member[0];
    int n = randint(0, 1)();
    a->member[1].repr[n] = b->member[1].repr[n];
    
    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}

void population::mutate(agent* a) {
    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}
