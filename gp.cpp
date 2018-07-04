/*************************
 * FILE: gp.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 *************************/

#include "gp.hpp"
#include "agent.hpp"

population::population() {
    leader = new agent(3);
}

population::~population() {
    delete leader;
}

// recombination and mutation
void population::breed() {
    return;
}

// hard stop the simulation
bool population::stop_condition() {
    return false;
}

// run the simulation at most n iterations
void population::run(int n) {
    for(int i = 0; i < n; ++i) {
        if (stop_condition()) break;

        breed();
    }
}
