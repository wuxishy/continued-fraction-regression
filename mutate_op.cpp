/***********************
 * FILE: mutate_op.cpp
 * AUTHOR: Haoyuan Sun
 * DATE: July, 2018
 ***********************/

#include "gp.hpp"

#include "fraction.hpp"
#include "func.hpp"

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
