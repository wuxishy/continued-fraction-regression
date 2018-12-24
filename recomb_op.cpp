/***********************
 * FILE: recomb_op.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

// recombination operations

#include "gp.hpp"

#include "optimize.hpp"

#include "agent.hpp"
#include "fraction.hpp"
#include "func.hpp"

template <typename Operator>
void population::variable_recomb(agent* a, agent* b, Operator op) {
    auto move_val = [&, this] (double a, double b) {
        return a + rint(-1, 4) * (b - a) / 3;
    };

    fraction& p1 = a->member[0];
    fraction& p2 = b->member[1];
    fraction& ch = a->member[1];

    for (int i = 0; i < num_var; ++i)
        ch.feature[i] = op(p1.feature[i], p2.feature[i]);

    size_t max_dep = std::min(ch.depth, std::min(p1.depth, p2.depth));
    
    for(size_t i = 0; i < 2*max_dep+1; ++i) {
        vector<double>& acoeff = p1.repr[i].coeff;
        vector<bool>& afeature = p1.repr[i].feature;
        vector<double>& bcoeff = p2.repr[i].coeff;
        vector<bool>& bfeature = p2.repr[i].feature;
        
        // find the shared varaiables
        vector<double> new_coeff(num_var+1);
        for(int j = 0; j < num_var; ++j) {
            if (!ch.feature[j]) {
                new_coeff[j] = 0;
                continue;
            }

            if (afeature[j] && bfeature[j]) {
                // six equally spaced points around the parents
                new_coeff[j] = move_val(acoeff[j], bcoeff[j]);
            }
            else if (afeature[j])
                new_coeff[j] = acoeff[j];
            else if (bfeature[j])
                new_coeff[j] = bcoeff[j];
        }

        new_coeff.back() = move_val(acoeff.back(), bcoeff.back());

        ch.repr[i].coeff = new_coeff;
        ch.repr[i].find_feature();
    }

    for(size_t i = 2*max_dep+1; i < ch.repr.size(); ++i) {
        for(int j = 0; j < num_var; ++j) {
            if (!ch.feature[j]) {
                ch.repr[i].coeff[j] = 0;
                ch.repr[i].feature[j] = false;
            }
        }
    }
}

void population::variable_intersect(agent* a, agent* b) {
    variable_recomb(a, b, std::bit_and<bool>());
}

void population::variable_union(agent* a, agent* b) {
    variable_recomb(a, b, std::bit_or<bool>());
}

void population::variable_symdiff(agent* a, agent* b) {
    variable_recomb(a, b, std::bit_xor<bool>());
}
