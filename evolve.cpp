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

void population::eval_fit(agent* a, int i) {
    a->fitness[i] = test_data.eval_fit(a->member[i]);
}

void population::recombine(agent* a, agent* b) {
    exchange_branch(a, b);

    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}

void population::mutate(agent* a) {
    if (rint(1, 20) != 1) return;

    leader_mutate(a);

    eval_fit(a, 1);

    a->update_pocket();
    a->propagate_pocket();
}
