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
    
    for(func& f : frac.repr) {
        if (frac.feature[i]) {
 	    f.coeff[i] = 0;
	    f.feature[i] = false;
	}
	else if (!f.feature[i]) {
	    f.coeff[i] = (rint(0, 1) ? 1 : -1) * rint(1, 3);
	    f.feature[i] = true;
	}
    }

    frac.feature[i] = !frac.feature[i];
}

// randomly turn on/off a variable from an existing feature
void population::feature_mod(fraction& frac) {
    vector<int> arr;
    for(size_t i = 0; i < frac.num_var; ++i) {
        if (frac.feature[i]) arr.push_back(i);
    }
    
    int i = rint(0, arr.size());
    int j;

    // constant feature
    if (i == arr.size()) {
        j = rint(1, frac.depth-1);

        frac.const_feature[j] = !frac.const_feature[j];
    }
    // variable feature
    else {
        i = arr[i];
        j = rint(0, frac.depth-1);
        func& f = frac.repr[j];

        if (f.feature[i]) f.coeff[i] = 0;
        else f.coeff[i] = (rint(0, 1) ? 1 : -1) * rint(1, 3);

        f.feature[i] = !f.feature[i];
    }
}
