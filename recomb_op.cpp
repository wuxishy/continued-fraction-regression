/***********************
 * FILE: recomb_op.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "gp.hpp"

#include "agent.hpp"
#include "fraction.hpp"
#include "func.hpp"

void population::variable_intersect(agent* a, agent* b) {
     // just random stuff for now
    a->member[1] = a->member[0];
    int n = rint(0, 1);
    a->member[1].repr[n] = b->member[1].repr[n];
}
