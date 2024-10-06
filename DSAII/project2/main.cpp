#include "./simulation-controller.hpp"
#include <iostream>

int main() {
    SimulationController sim = SimulationController();

    sim.runSimulation("test1.txt");
    std::cout << std::endl;
    sim.runSimulation("test2.txt");

    return 0;
}