#ifndef __GP_HPP
#define __GP_HPP

#include <algorithm>

#include "rng.hpp"

struct population {
    population();
    ~population();

    void initialize();
    void initialize(int len);

    void breed();

    void run(int gen);
};

#endif // __GP_HPP
