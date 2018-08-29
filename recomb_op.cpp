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

static inline double move_val(randint& rand, double a, double b) {
    return a + rand(-1, 4) * (b - a) / 3;
}

template <typename Operator>
void population::variable_recomb(agent* a, agent* b, Operator op) {
    fraction& p1 = a->member[0];
    fraction& p2 = b->member[1];
    fraction& ch = a->member[1];

    for (int i = 0; i < test_data.num_var; ++i)
        ch.feature[i] = op(p1.feature[i], p2.feature[i]);

    int max_dep = std::min(ch.depth, std::min(p1.depth, p2.depth));
    
    for(int i = 0; i < max_dep; ++i) {
        vector<double>& acoeff = p1.repr[i].coeff;
        vector<bool>& afeature = p1.repr[i].feature;
        vector<double>& bcoeff = p2.repr[i].coeff;
        vector<bool>& bfeature = p2.repr[i].feature;
        
        // find the shared varaiables
        vector<double> new_coeff(test_data.num_var);
        for(int j = 0; j < test_data.num_var; ++j) {
            if (!ch.feature[j]) {
                new_coeff[j] = 0;
                continue;
            }

            if (afeature[j] && bfeature[j]) {
                // six equally spaced points around the parents
                new_coeff[j] = move_val(rint, acoeff[j], bcoeff[j]);
            }
            else if (afeature[j])
                new_coeff[j] = acoeff[j];
            else if (bfeature[j])
                new_coeff[j] = bcoeff[j];
        }

        ch.repr[i].coeff = new_coeff;
        ch.repr[i].find_feature();

        ch.const_feature[i] = op(p1.const_feature[i], p2.const_feature[i]);
    }

    for(int i = max_dep; i < ch.depth; ++i) {
        for(int j = 0; j < test_data.num_var; ++j) {
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
