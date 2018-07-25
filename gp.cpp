/*************************
 * FILE: gp.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 *************************/

/* the most basic functionalities of a GP program
 * the fancy stuff are not here
 */

#include "gp.hpp"
#include "agent.hpp"
#include "optimize.hpp"

#include <cassert>
#include <iostream>
#include <deque>

population::population(data_store td) : test_data(td) {
    root = new agent(4);

    rint = randint();

    initialize(root);
}

population::~population() {
    delete root;
}

// recombination
void population::breed(agent* leader) {
    mutate(leader);

    // reached a leaf
    if (leader->depth <= 1) return;

    std::size_t n = leader->degree;

    //print();
    assert(check(root));

    recombine(leader, leader->children[n-1]);

    recombine(leader->children[n-1], leader);

    for(std::size_t i = 0; i < n-1; ++i) {
        recombine(leader->children[i], leader->children[i+1]);
    }

    for(std::size_t i = 0; i < n; ++i)
        breed(leader->children[i]);

}

// hard stop the simulation
bool population::stop_condition() {
    return false;
}

// run the simulation at most n iterations
void population::run(int n) {
    for(int i = 0; i < n; ++i) {
        if (stop_condition()) break;
        
        // old age kill
        if (i % 25 == 0) {
            print();
            
            root->member[0] = fraction(test_data.num_var);
            eval_fit(root, 0);

            root->movedown_pocket();
        }

        breed(root);
    }
    print();
    //test_data.print_val("data.out", root->member[0]);
}

bool population::check(agent* a) {
    if (a->fitness[0] > a->fitness[1]) return false;

    if (a->depth <= 1) return true;

    for(std::size_t i = 0; i < a->degree; ++i) {
        if (!check(a->children[i])) return false;

        if (a->fitness[0] > a->children[i]->fitness[0]) return false;
    }

    return true;
}

// for debug only
void population::print() {
    std::cout.precision(5);
    std::cout << root->fitness[0] << ' ';
    std::cout.precision(2);
    root->member[0].show(std::cout);
    std::cout << std::endl;

    std::cout.precision(5);
    std::cout << root->fitness[1] << ' ';
    std::cout.precision(2);
    root->member[1].show(std::cout);
    std::cout << std::endl;
    
    std::cout.precision(5);
    std::cout << root->children[2]->fitness[1] << ' ';
    std::cout.precision(2);
    root->children[2]->member[1].show(std::cout);
    std::cout << std::endl;

    std::cout << std::endl;
    /*
    std::deque<agent*> q;
    q.push_back(root);
    q.push_back(nullptr);

    while(!q.empty()) {
        agent* c = q.front();
        q.pop_front();
        if (!c) {
            printf("\n");
            if(q.empty()) break;
            q.push_back(nullptr);
            continue;
        }
        printf("[%.1f, %.1f] %.2f, [%.1f, %.1f] %.2f; ", c->member[0].repr[0].coeff[0], c->member[0].repr[1].coeff[0], c->fitness[0], c->member[1].repr[0].coeff[0], c->member[1].repr[1].coeff[0], c->fitness[1]);
        if(c->depth > 1) 
            for(std::size_t i = 0; i < c->degree; ++i) q.push_back(c->children[i]); 
    }
    printf("\n");
    */
}
