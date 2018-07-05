/***********************
 * FILE: evolve.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "gp.hpp"
#include "agent.hpp"

void population::recombine(agent* a, agent* b) {

    a->update_pocket();
    a->propagate_pocket();
}

void population::mutate(agent* a) {
    a->update_pocket();
    a->propagate_pocket();
}
