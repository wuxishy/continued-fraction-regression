/*********************
 * FILE: gp.hpp         
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 *********************/

// where everything happens

#ifndef __GP_HPP
#define __GP_HPP

// forward declare
class agent;
class fraction;

// include
#include <vector>
#include "rng.hpp"
#include "data.hpp"

class population {
private:
    data_store test_data;

    agent* root;

    randint rint;

    // init.cpp
    void initialize(agent* current);

    // evolve.cpp
    void eval_fit(agent* a, int i);
    void recombine(agent* a, agent* b);
    void mutate(agent* a);
    void local_search(agent* a);
    void diversify(agent* a);
    void simplify(agent* a);

    // recomb_op.cpp
    void variable_intersect(agent* a, agent* b);
    void variable_union(agent* a, agent* b);
    void exchange_branch(agent* a, agent* b);

    // mutate_op.cpp
    void feature_toggle(fraction& frac);

    // gp.cpp
    void breed(agent* leader);
    bool stop_condition();

    // debug stuff
    bool check(agent* a);
    void print();

public:
    population(data_store td);
    ~population();

    void run(int gen);
};

#endif // __GP_HPP
