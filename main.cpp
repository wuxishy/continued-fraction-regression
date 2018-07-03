#include "agent.hpp"

int main(int argv, char** argc) {
    agent* smith = new agent(3);

    delete smith;
    return 0;
}
