/*********************
 * FILE: agent.hpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 *********************/

#ifndef __AGENT_HPP
#define __AGENT_HPP

// include
#include "fraction.hpp"

class agent {
private:
    int depth;  // the depth below this node (inclusive), leaves has depth 1
    int degree; // the degree of the tree structure, default is 3

    agent* parent;
    agent** children;

    // 0 is pocket, 1 is current
    fraction member[2];
    double fitness[2];

    static void swap(agent* a, int i, agent* b, int j);

    void update_pocket();
    void propagate_pocket();

public:
    agent(int dep, int deg = 3);
    ~agent();

    void update();

    friend class population;
};

#endif // __AGENT_HPP
