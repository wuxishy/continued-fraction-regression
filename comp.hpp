/***********************
 * FILE: comp.cpp
 * AUTHOR: Haoyuan Sun
 * Date: August, 2018
 ***********************/

// work around issues with NaN by creating
// our own comparison functor
// satisfies strict total ordering

#include <cmath>

struct comp_less {
    bool operator() (double a, double b) const {
        if (!std::isfinite(a)) return false;
        if (!std::isfinite(b)) return true;

        return a < b;
    }
};

struct comp_greater {
    bool operator() (double a, double b) const {
        if (!std::isfinite(b)) return false;
        if (!std::isfinite(a)) return true;

        return a > b;
    }
};
