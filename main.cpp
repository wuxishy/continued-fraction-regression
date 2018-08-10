#include "data.hpp"

#include "gp.hpp"

#include "optimize.hpp"

#include <string>
#include <iostream>

int main(int argv, char** argc) {
    data_store test_data;

    test_data.read("data.in");

    population ant(test_data);

    if (argv == 1) ant.run(200);
    else ant.run(std::stoi(argc[1]));

    return 0;
}
