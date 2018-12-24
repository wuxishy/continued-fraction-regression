#include "data.hpp"

#include "gp.hpp"
#ifdef __linux__
#include <signal.h>
#endif

#include <string>
#include <iostream>

#include <chrono>

volatile bool STOP = false;
void mark_stop(int signum) {
    STOP = true;
}

int main(int argv, char** argc) {
    signal(SIGINT, mark_stop);
    
    data_store test_data, train_data;

    train_data.read("data.in");
    test_data.read("test.in");

    population ant(train_data, test_data);

    auto start = std::chrono::system_clock::now();

    if (argv == 1) ant.run(200);
    else ant.run(std::stoi(argc[1]));

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end-start;

    std::cout.precision(3);
    std::cout << "======================\n";
    std::cout << "Time in seconds: " << diff.count() << "\n";
    std::cout << "Time in minutes: " << diff.count() / 60 << "\n";

    return 0;
}
