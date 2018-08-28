#include "data.hpp"

#include "gp.hpp"
#ifdef __linux__
#include <signal.h>
#endif

#include <string>
#include <iostream>

volatile bool STOP = false;
void mark_stop(int signum) {
    STOP = true;
}

int main(int argv, char** argc) {
    signal(SIGINT, mark_stop);
    
    data_store test_data;

    test_data.read("data.in");
    population ant(test_data);

    if (argv == 1) ant.run(200);
    else ant.run(std::stoi(argc[1]));
  
    return 0;
}
