#include <ctime>
#include <iostream>
#include <fstream>
#include <random>
#include <string>

#include "r_local_simulator.h"

int main(int argc, char**argv) {

  int rounds = 50; //Number of rounds of generation to simulate in test

  srand((long)1); //Seed the random number generator with the same seed every time!
  std::ofstream myfile;
  if (argc>0) {
  myfile.open(argv[1]);
  }

  rLocalSimulator my_sim;

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
