/*************************
 * FILE: gp.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 *************************/

#include "gp.hpp"
#include "agent.hpp"
#include <cassert>

population::population(std::vector<double>& e, 
        std::vector<std::vector<double>>& d) : expected(e), data(d) {
    num_entry = expected.size();
    num_var = data[0].size();
    assert(num_var > 0);
    assert(num_entry == d.size());

    root = new agent(3);
}

population::~population() {
    delete root;
}

// recombination
void population::breed(agent* leader) {
    // reached a leaf
    if (leader->depth <= 1) return;

    int n = leader->degree;
    recombine(leader, leader->children[n-1]);
    recombine(leader->children[n-1], leader);

    for(int i = 0; i < n-1; ++i) {
        recombine(leader->children[i], leader->children[i+1]);
    }

    for(int i = 0; i < n; ++i)
        breed(leader->children[i]);
}

// hard stop the simulation
bool population::stop_condition() {
    return false;
}

// run the simulation at most n iterations
void population::run(int n) {
    for(int i = 0; i < n; ++i) {
        if (stop_condition()) break;

        breed(root);
    }
}
