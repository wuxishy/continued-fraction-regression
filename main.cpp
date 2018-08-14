#include "data.hpp"
#include "gp.hpp"

#include "optimize.hpp"

#include <string>
#include <iostream>

int main(int argv, char** argc) {
    data_store test_data;

    test_data.read("data.in");

    int iter = (argv == 1 ? 200 : std::stoi(argc[1]));

    for (int i = 0; i < 3; ++i) {
        population ant(test_data);
        fraction sol = ant.run(iter);
        test_data = test_data.gen_error(sol);
    }

    return 0;
}
