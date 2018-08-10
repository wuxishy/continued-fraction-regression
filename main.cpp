#include "data.hpp"

#include "gp.hpp"

#include <string>
#include <iostream>

#include "agent.hpp"

int main(int argv, char** argc) {
    /*
    agent* a = new agent(2, 1);
    a->fitness[0] = 1;
    a->children[0]->fitness[0] = -1;
    a->movedown_pocket();
    std::cout << a->fitness[0] << ' ' << a->children[0]->fitness[0] << '\n';
    */
    data_store test_data;

    test_data.read("data.in");

    population ant(test_data);

    if (argv == 1) ant.run(200);
    else ant.run(std::stoi(argc[1]));
    
    return 0;
}
