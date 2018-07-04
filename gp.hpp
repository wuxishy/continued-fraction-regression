/*********************
 * FILE: gp.hpp         
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 *********************/

#ifndef __GP_HPP
#define __GP_HPP

// forward declare
class agent;

// include
#include <algorithm>
#include "rng.hpp"

class population {
private:
    agent* leader;

    static void initialize(agent* current);

    void breed();

    bool stop_condition();
    
public:
    population();
    ~population();


    void run(int gen);
};

#endif // __GP_HPP
