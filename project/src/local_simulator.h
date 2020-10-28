/**
 * @file local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_LOCAL_SIMULATOR_H_
#define SRC_LOCAL_SIMULATOR_H_

#include <vector>

#include "src/simulator.h"

class LocalSimulator : public Simulator {
 public:
 /**
 * @brief Set up the simulator and set default ostream as std::cout
 *
 * @return boolean
 */
  bool Start(std::ostream& = std::cout) override;
  /**
  * @brief Update simulator(bus and route) and set default ostream as std::cout
  *
  * @return boolean
  */
  bool Update(std::ostream& = std::cout) override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_LOCAL_SIMULATOR_H_
