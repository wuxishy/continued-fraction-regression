/***********************
 * FILE: agent.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "agent.hpp"

agent::agent(std::size_t dep, std::size_t deg) : depth(dep), degree(deg) {
    this->parent = nullptr;

    if (depth > 1) {
        children = new agent*[degree];

        for(std::size_t i = 0; i < degree; ++i) {
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
        for(std::size_t i = 0; i < degree; ++i) delete children[i];
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

void agent::movedown_pocket() {
    update_pocket();

    // already a leaf
    if (depth <= 1) return;

    int best_child = 0;
    double best_fit = this->children[0]->fitness[0];
    for(std::size_t i = 1; i < degree; ++i) {
        if (children[i]->fitness[0] < best_fit) {
            best_child = i;
            best_fit = children[i]->fitness[0];
        }
    }

    if (fitness[0] > best_fit) {
        swap(this, 0, children[best_child], 0);
        children[best_child]->movedown_pocket();
    }
}

void agent::propagate_pocket() {
    // already the leader
    if (!this->parent) return;

    if(fitness[0] < this->parent->fitness[0]) {
        agent::swap(this, 0, this->parent, 0);
        return this->parent->propagate_pocket();
    }
}
