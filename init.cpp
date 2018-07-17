/*********************
 * FILE: init.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2016
 *********************/

#include "gp.hpp"
#include "agent.hpp"

void population::initialize(agent *current) {
    current->member[0] = fraction(test_data.num_var);
    current->member[1] = fraction(test_data.num_var);

    eval_fit(current, 0);
    eval_fit(current, 1);

    if (current->depth > 1) {
        for(std::size_t i = 0; i < current->degree; ++i) 
            initialize(current->children[i]);
    }

    current->movedown_pocket();
}
