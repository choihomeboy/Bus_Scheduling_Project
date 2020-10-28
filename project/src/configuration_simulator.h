/**
 * @file local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_CONFIGURATION_SIMULATOR_H_
#define SRC_CONFIGURATION_SIMULATOR_H_

#include <vector>

#include "src/simulator.h"

class ConfigurationSimulator : public Simulator {
 public:
  /**
  * @brief Construct the configuration simulator with default variables
  *      routes, length of simulation, outout file)
  * @param[in] vector holding routes
  * @param[in] integer holding length of simulation
  * @param[in] ostream holding outout file
  *
  */
  ConfigurationSimulator(std::vector<Route *> = std::vector<Route *>(),
                          int = 20, std::ostream * = &(std::cout));
  /**
  * @brief setup the simulation
  *
  * @return boolean true when it sets up without error
  */
  bool Start(std::ostream& = std::cout) override;
  /**
  * @brief Update the simulation as timestep passes
  *
  * @return boolean true when it works fine
  */
  bool Update(std::ostream& = std::cout) override;

 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
  std::ostream *out_;
  std::vector<Route *> routes_;
  int rounds_ = 20;
};

#endif  // SRC_CONFIGURATION_SIMULATOR_H_
