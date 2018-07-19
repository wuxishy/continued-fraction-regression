#include "data.hpp"

#include "gp.hpp"

#include "optimize.hpp"

#include <cstdio>

int main(int argv, char** argc) {
    data_store test_data;

    test_data.read("data.in");

    population ant(test_data);

    ant.run(150);

    return 0;
}
