/**
 * @file configuration_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <fstream>

#include "src/config_manager.h"
#include "src/configuration_simulator.h"

int main(int argc, char**argv) {
  // NOTE: this usage will change depending on
  //       how you build your config_sim classes
  //   E.g., how will you handle getting the length of simulation value?
  std::cout << "Usage: ./build/bin/configuration_sim <config_filename> ";
  std::cout << "<length of simulation> <output file>";
  std::cout << std::endl;

  int rounds;
  if (argc == 4) {
    // Checking invalid input
    std::ifstream f;
    std::string temp = argv[1];
    std::cout << temp << std::endl;
    f.open("config/" + temp);
    if ( f.fail() ) {
      std::cout<< "Error : Not existing config file" << std::endl;
      return 0;
    }

    rounds = std::stoi(argv[2]);
    if (rounds < 0) {
      std::cout<< "Error : rounds have to be more than equal to 0" << std::endl;
      return 0;
    }
    ConfigManager con;
    con.ReadConfig(argv[1]);
    std::ofstream myfile;
    myfile.open(argv[3]);
    ConfigurationSimulator config_sim = ConfigurationSimulator(con.GetRoutes(),
                                                        rounds, &(myfile));
    // std::ofstream myfile;
    // myfile.open(argv[1]);
    // config_sim.Update(myfile);

    myfile << "/*************************" << std::endl << std::endl;
    myfile << "         STARTING" << std::endl;
    myfile << "        SIMULATION" << std::endl;
    myfile << "*************************/" << std::endl;

    config_sim.Start(myfile);

    myfile << "/*************************" << std::endl << std::endl;
    myfile << "           BEGIN" << std::endl;
    myfile << "          UPDATING" << std::endl;
    myfile << "*************************/" << std::endl;

    for (int i = 0; i < rounds; i++) {
      config_sim.Update(myfile);
    }

    myfile << "/*************************" << std::endl << std::endl;
    myfile << "        SIMULATION" << std::endl;
    myfile << "         COMPLETE" << std::endl;
    myfile << "*************************/" << std::endl;
  } else {
    std::cout << "Input does not match the required usage, using defaults:"
    << std::endl << "./build/bin/configuration_sim config.txt 20 std::cout"
                                                              << std::endl;
    rounds = 20;
    ConfigManager con;
    con.ReadConfig("config.txt");
    ConfigurationSimulator config_sim =
                    ConfigurationSimulator(con.GetRoutes(), 20, &(std::cout));

    std::cout << "/*************************" << std::endl << std::endl;
    std::cout << "         STARTING" << std::endl;
    std::cout << "        SIMULATION" << std::endl;
    std::cout << "*************************/" << std::endl;

    config_sim.Start(std::cout);

    std::cout << "/*************************" << std::endl << std::endl;
    std::cout << "           BEGIN" << std::endl;
    std::cout << "          UPDATING" << std::endl;
    std::cout << "*************************/" << std::endl;

    for (int i = 0; i < rounds; i++) {
      config_sim.Update(std::cout);
    }

    std::cout << "/*************************" << std::endl << std::endl;
    std::cout << "        SIMULATION" << std::endl;
    std::cout << "         COMPLETE" << std::endl;
    std::cout << "*************************/" << std::endl;
  }

  // Check command line params for config file name

  // if filename arg present
  //   Create ConfigManager
  //   Call ReadConfig
  //   Create ConfigurationSimulator
  //   Call Start on ConfigurationSimulator
  //   Start for loop, length of simulation (where from?)
  //     Call Update on ConfigurationSimulator
  // else
  //   echo info to the user about needing a config file name

  return 0;
}
