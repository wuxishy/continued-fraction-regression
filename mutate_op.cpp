/***********************
 * FILE: mutate_op.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: August, 2018
 ***********************/

#include "gp.hpp"

#include "fraction.hpp"
#include "func.hpp"

#include <vector>
using std::vector;
using std::size_t;

// fewer feature -> high chance of turning on a feature
void population::feature_toggle(fraction& frac) {
    int i = rint(0, frac.num_var - 1);
    
    bool on = false;
    for(func& f : frac.repr) on |= f.feature[i];
    
    for(func& f : frac.repr) {
        if (on) {
 	    f.coeff[i] = 0;
	    f.feature[i] = false;
	}
	else if (!f.feature[i]) {
	    f.coeff[i] = (rint(0, 1) ? 1 : -1) * rint(1, 3);
	    f.feature[i] = true;
	}
    }
}

// randomly turn on all variables from an existing feature
void population::expand_feature(fraction& frac) {
    vector<int> arr;
    for(size_t i = 0; i < frac.num_var; ++i) {
        bool on = false;
        for (func& f : frac.repr) on |= f.feature[i];

        if (on) arr.push_back(i);
    }
    
    if (arr.empty()) return;
    int ind = arr[rint(0, arr.size()-1)];

    for(func& f : frac.repr)
        if (!f.feature[ind]) {
            f.coeff[ind] = (rint(0, 1) ? 1 : -1) * rint(1, 3);
            f.feature[ind] = true;
        }
}
