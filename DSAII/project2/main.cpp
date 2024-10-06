#include "./simulation-controller.hpp"

int main() {
    SimulationController sim = SimulationController();

    sim.runSimulation("test1.txt");
    sim.runSimulation("test2.txt");

    return 0;
}