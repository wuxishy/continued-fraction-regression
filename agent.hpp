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

public:
    fraction pocket;
    fraction current;

    agent();
    ~agent();
}

#endif // __AGENT_HPP
