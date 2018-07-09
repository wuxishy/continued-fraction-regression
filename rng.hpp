/**********************
 * FILE: rng.hpp
 * AUTHOR: Haoyuan Sun
 * Date: April, 2018
 **********************/

// wrapper around STL's built-in pseudorandom number
// generator functionalities

#ifndef __RNG_HPP
#define __RNG_HPP

#include <random>

class randint {
private:
    std::mt19937 gen;

public:
    randint () {
        std::random_device rd;
        gen.seed(rd());
    }

    int operator() (int a, int b) {
        return std::uniform_int_distribution<> (a, b) (gen);
    }
};

class randreal {
private:
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

public:
    randreal() {
        std::random_device rd;
        gen.seed(rd());
        dis = std::uniform_real_distribution<> (0, 1);
    }

    double operator() () {
        return dis(gen);
    }
};

#endif // __RNG_HPP
