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
