// Copyright 2019 Yongwoo Choi


#include <ctime>
#include <iostream>
#include <fstream>
#include <random>
#include <string>

#include "src/faster_r_local_simulator.h"

int main(int argc, char**argv) {
  int rounds = 50;  // Number of rounds of generation to simulate in test

  srand((int64_t)time(NULL));  // Seed the random number generator...

  std::ofstream myfile;
  if (argc == 2) {
    myfile.open(argv[1]);
  } else {
    std::cout << "Not a file given to save output. Please enter follow:";
    std::cout << std::endl;
    std::cout << "Usage: ./build/bin/faster_regression_test "
    << "<output file> ";
    return 0;
  }

  FasterrLocalSimulator my_sim;

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


  return 0;
}
