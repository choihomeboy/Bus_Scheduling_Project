// Copyright 2019 Kevin Wendt
#include <ctime>
#include <iostream>
#include <fstream>
#include <random>

#include "src/local_simulator.h"

int main(int argc, char* argv[]) {
  int rounds = 20;  // Number of rounds of generation to simulate in test

  srand((int64_t)time(NULL));  // Seed the random number generator...

  LocalSimulator my_sim;

  if (argc > 1) {
    std::ofstream myfile;
    myfile.open(argv[1]);
    my_sim.Update(myfile);

    myfile << "/*************************" << std::endl << std::endl;
    myfile << "         STARTING" << std::endl;
    myfile << "        SIMULATION" << std::endl;
    myfile << "*************************/" << std::endl;

    my_sim.Start(myfile);

    myfile << "/*************************" << std::endl << std::endl;
    myfile << "           BEGIN" << std::endl;
    myfile << "          UPDATING" << std::endl;
    myfile << "*************************/" << std::endl;

    for (int i = 0; i < rounds; i++) {
      my_sim.Update(myfile);
    }

    myfile << "/*************************" << std::endl << std::endl;
    myfile << "        SIMULATION" << std::endl;
    myfile << "         COMPLETE" << std::endl;
    myfile << "*************************/" << std::endl;
  } else {
    std::cout << "User does not provide file name for output, using default: ";
    std::cout << "std::cout" << std::endl;
    std::cout << "/*************************" << std::endl << std::endl;
    std::cout << "         STARTING" << std::endl;
    std::cout << "        SIMULATION" << std::endl;
    std::cout << "*************************/" << std::endl;

    my_sim.Start(std::cout);

    std::cout << "/*************************" << std::endl << std::endl;
    std::cout << "           BEGIN" << std::endl;
    std::cout << "          UPDATING" << std::endl;
    std::cout << "*************************/" << std::endl;

    for (int i = 0; i < rounds; i++) {
      my_sim.Update(std::cout);
    }

    std::cout << "/*************************" << std::endl << std::endl;
    std::cout << "        SIMULATION" << std::endl;
    std::cout << "         COMPLETE" << std::endl;
    std::cout << "*************************/" << std::endl;
  }

  return 0;
}
