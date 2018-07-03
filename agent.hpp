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

public:
    fraction pocket;
    fraction current;

    agent(int dep, int deg = 3);
    ~agent();
};

#endif // __AGENT_HPP
