#include "reader.hpp"
#include "gp.hpp"

#include <cstdio>

int main(int argv, char** argc) {
    std::vector<double> expected;
    std::vector<std::vector<double>> data;

    reader("data.in", expected, data);

    population ant(expected, data);

    ant.run(5);

    return 0;
}
