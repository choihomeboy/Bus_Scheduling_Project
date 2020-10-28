
/**
 * @file passenger.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_

#include <iostream>
#include <string>
/**
 * @brief The main class for the acitivity of the passenger.
 *
 */
class Passenger {  // : public Reporter {
 public:
  /**
  * @brief Constructs a passenger with a standard name and id.
  *
  *
  * @param[in] int holding an id number
  * @param[in] string holding a name of a created passenger.
  *
  */
  explicit Passenger(int = -1, std::string = "Nobody");
  /**
  * @brief Update the passengers' wait at stop and time on bus
  *
  */
  void Update();
  /**
  * @brief Update the passengers' wait at stop or time on bus
  *
  */
  void GetOnBus();
  /**
  * @brief Check how long the passenger has spent time in bus and at stop
  *
  * @return wait at stop + time on bus
  */
  int GetTotalWait() const;
  /**
  * @brief Check if the on_bus_ is true, which means passenger is on the bus.
  *
  * @return true when on_bus_ is true
  */
  bool IsOnBus() const;
  /**
  * @brief Check which destination the passenger is planning to go
  *
  * @return Destination stop id integer
  */
  int GetDestination() const;
  /**
  * @brief Report important information into ostream defined
  *
  */
  void Report(std::ostream&) const;

 private:
  std::string name_;
  /**
   * @brief check which stop the bus is approaching
   *
   * @return approaching stop id
   */
  int destination_stop_id_;
  int wait_at_stop_;
  int time_on_bus_;
  int id_;
  /**
   * @brief check if the passenger is on the bus; created
   *        to prevent time conflict at the passenger update
   *
   */
  bool on_bus_;
  /**
   * @brief global count, used to set ID for new instances
   *
   */
  static int count_;   //!<
};

#endif  // SRC_PASSENGER_H_
