/************************
 * FILE: optimize.cpp
 * AUTHOR: Haoyuan Sun
 * Date: July, 2018
 ************************/

// performing local search

#include "optimize.hpp"
#include "gp.hpp"

#include <map>

optimize::optimize(data_store& td, fraction& f) : 
        test_data(td), frac(f) {
    local_copy = frac; 

    for(size_t i = 0; i < frac.repr.size(); ++i) {
        for(size_t j = 0; j < frac.repr[i].coeff.size(); ++j) {
            if(frac.repr[i].feature[j]) {
                ++ndim;
                var_map.push_back({i, j});
            }
        }
    }
}

void optimize::run (int type) {
    switch(type) {
        case 1:
            nelder_mead();
            break;
        default:
            break;
    }
}

double optimize::eval_fit() {
    return test_data.eval_fit(local_copy);
}

// simplified nelder mead for speed
void optimize::nelder_mead () {
}
