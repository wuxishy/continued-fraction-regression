/***********************
 * FILE: agent.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "agent.hpp"

agent::agent(int dep, int deg) : depth(dep), degree(deg) {
    this->parent = nullptr;

    if (depth > 1) {
        children = new agent*[degree];

        for(int i = 0; i < degree; ++i) {
            children[i] = new agent(depth-1, degree);
            children[i]->parent = this;
        }
    }
    else {
        children = nullptr;
    }
}

agent::~agent() {
    if (depth > 1) {
        for(int i = 0; i < degree; ++i) delete children[i];
        delete[] children;
    }
}

void agent::swap(agent* a, int i, agent* b, int j) {
    double tmp_fit = a->fitness[i];
    a->fitness[i] = b->fitness[j];
    b->fitness[j]  = tmp_fit;

    fraction tmp_frac = a->member[i];
    a->member[i] = b->member[j];
    b->member[j] = tmp_frac;
}

void agent::update_pocket() {
    if(fitness[0] > fitness[1]) 
        agent::swap(this, 0, this, 1);
}

void agent::propagate_pocket() {
    // already the leader
    if (!this->parent) return;

    if(fitness[0] > this->parent->fitness[0]) {
        agent::swap(this, 0, this->parent, 0);
        return this->parent->propagate_pocket();
    }
}
