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

void population::variable_intersect(agent* a, agent* b) {
    fraction& p1 = a->member[0];
    fraction& p2 = b->member[1];
    fraction& ch = a->member[1];

    int ind = rint(1, std::min(p1.depth, std::min(ch.depth, p2.depth))) - 1;
    
    vector<double>& acoeff = p1.repr[ind].coeff;
    vector<bool>& afeature = p1.repr[ind].feature;
    vector<double>& bcoeff = p2.repr[ind].coeff;
    vector<bool>& bfeature = p2.repr[ind].feature;
    
    // find the shared varaiables
    vector<double> new_coeff(test_data.num_var);
    for(int i = 0; i < test_data.num_var; ++i) {
        if (afeature[i] && bfeature[i]) {
            // six equally spaced points around the parents
            new_coeff[i] = move_val(rint, acoeff[i], bcoeff[i]);
        }
    }

    ch.repr[ind].coeff = new_coeff;
    ch.repr[ind].find_feature();

    ch.const_feature[ind] = p1.const_feature[ind] & p2.const_feature[ind];
}

void population::variable_union(agent* a, agent* b) {
    fraction& p1 = a->member[0];
    fraction& p2 = b->member[1];
    fraction& ch = a->member[1];

    int ind = rint(1, std::min(p1.depth, std::min(ch.depth, p2.depth))) - 1;
    
    vector<double>& acoeff = p1.repr[ind].coeff;
    vector<bool>& afeature = p1.repr[ind].feature;
    vector<double>& bcoeff = p2.repr[ind].coeff;
    vector<bool>& bfeature = p2.repr[ind].feature;
    
    // find the shared varaiables
    vector<double> new_coeff(test_data.num_var);
    for(int i = 0; i < test_data.num_var; ++i) {
        if (afeature[i] && bfeature[i]) {
            // six equally spaced points around the parents
            new_coeff[i] = move_val(rint, acoeff[i], bcoeff[i]);
        }
        else if (afeature[i])
            new_coeff[i] = acoeff[i];
        else if (bfeature[i])
            new_coeff[i] = bcoeff[i];
    }

    ch.repr[ind].coeff = new_coeff;
    ch.repr[ind].find_feature();

    ch.const_feature[ind] = p1.const_feature[ind] | p2.const_feature[ind];
}
/* bad operator
void population::exchange_branch(agent* a, agent* b) {
    int ind = rint(1, std::min(a->member[0].repr.size(), 
                b->member[1].repr.size())) - 1;

    // make a cut
    a->member[1].constant = a->member[0].constant;
    a->member[1].constant.resize(ind);
    a->member[1].repr = a->member[0].repr;
    a->member[1].repr.resize(ind);

    // copy the branch from b to a;
    for(size_t i = ind; i < b->member[1].repr.size(); ++i) {
        a->member[1].constant.push_back(b->member[1].constant[i]);
        a->member[1].repr.push_back(b->member[1].repr[i]);
    }
    
    a->member[1].depth = b->member[1].depth;
}
*/
