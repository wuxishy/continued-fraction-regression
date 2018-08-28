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

#include "eval.hpp"

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
    recombine(leader, leader->children[n-1]);

    recombine(leader->children[n-1], leader);

    for(std::size_t i = 0; i < n-1; ++i) {
        recombine(leader->children[i], leader->children[i+1]);
    }

    for(std::size_t i = 0; i < n; ++i)
        breed(leader->children[i]);

    if (!check(root)) {
        std::cerr << "Recombination!\n";
        assert(false);
    }
}

// hard stop the simulation
bool population::stop_condition() {
    if (STOP) return true;

    return false;
}

// run the simulation at most n iterations
void population::run(int n) {
    double best = root->fitness[0];
    fraction sol = root->member[0];
    double cur_best = root->fitness[0];

//    simplify(root);

    int counter = 0;
    for(int i = 1; i <= n; ++i) {
        if (stop_condition()) break;

        breed(root);
        
//        if (i % 20 == 0)
//            simplify(root);

        if (i % 1 == 0) {
//            diversify(root);

            local_search(root);

            if (!check(root)) {
                std::cerr << i << " Local search!\n";
		print_tree();
                assert(false);
            }
            
            if (root->fitness[0] >= cur_best) ++counter;
            else counter = 0;

            // kill if the best solution got stuck
            if (counter > 5) {
                root->member[0] = fraction(test_data.num_var);
                eval_fit(root, 0);

                root->movedown_pocket();

                counter = 0;
            }

            if (!check(root)) {
                std::cerr << "Old-age!\n";
		print_tree();
                assert(false);
            }
            
            print();
        }

        cur_best = root->fitness[0];
        if (cur_best < best) {
            best = cur_best;
            sol = root->member[0];
        }
    }
    
    evaluator e(test_data);
    
    std::cout.precision(5);
    std::cout << e.eval_fit(sol) << "\n";
    std::cout << sol.num_feature() << ' ' << best << "\n";
    std::cout.precision(3);
    sol.show_latex(std::cout);
    std::cout << std::endl;
    sol.show_math(std::cout);
    std::cout << std::endl;

    e.print_val("data.out.csv", sol);
}

bool population::check(agent* a) {
    if (a->fitness[0] > a->fitness[1]) {
        std::cerr << "Pocket! " << a->depth << ' ' << a->fitness[0] << ' ' << a->fitness[1] << std::endl;
        return false;
    }

    if (a->depth <= 1) return true;

    for(std::size_t i = 0; i < a->degree; ++i) {
        if (!check(a->children[i])) return false;

        if (a->fitness[0] > a->children[i]->fitness[0]) {
            std::cerr << "Parent! " << a->depth << ' ' << a->fitness[0] << ' ' << a->children[i]->fitness[0] << std::endl;
            return false;
        }
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
    /*
    std::cout.precision(5);
    std::cout << root->children[2]->fitness[1] << ' ';
    std::cout.precision(2);
    root->children[2]->member[1].show(std::cout);
    std::cout << std::endl;
    */
    std::cout << std::endl;
    
}

void population::print_tree() {
    std::deque<agent*> q;
    q.push_back(root);

    while(!q.empty()) {
	agent* a = q.front();
	q.pop_front();
	std::cout << a->fitness[0] << ' ';
	if(a->depth > 1) 
	    for (std::size_t i = 0; i < a->degree; ++i)
                q.push_back(a->children[i]);

	if(q.empty() || q.front()->depth < a->depth)
	    std::cout << '\n';
    }
}
