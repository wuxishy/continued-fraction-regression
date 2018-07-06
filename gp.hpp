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
#include <vector>
#include "rng.hpp"

class population {
private:
    std::size_t num_var;
    std::size_t num_entry;

    std::vector<double> expected;
    std::vector<std::vector<double>> data;

    agent* root;

    void initialize(agent* current);

    void eval_fit(agent* a, int i);

    void recombine(agent* a, agent* b);
    void mutate(agent* a);
    void breed(agent* leader);

    bool stop_condition();

    // debug stuff
    bool check(agent* a);
    void print();
public:
    population(std::vector<double>& e, std::vector<std::vector<double>>& d);
    ~population();

    void run(int gen);
};

#endif // __GP_HPP
