/**
 * @file stop.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_STOP_H_
#define SRC_STOP_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <list>
#include <iostream>

#include "src/bus.h"
#include "src/passenger.h"

class Bus;
/**
 * @brief The main class for the acitivity of the stop.
 *
 */
class Stop {
 public:
   /**
   * @brief Constructs a stop with a id and destination location
   *
   *
   * @param[in] int holding an id number
   * @param[in] double holding a longtitude.
   * @param[in] double holding a latitude.
   */
  explicit Stop(int, double = 44.973723, double = -93.235365);
  /**
  * @brief Getter stop id
  *
  * @return stop id
  */
  int GetId() const;
  /**
  * @brief Adding passengers to the stop (from the generator)
  *
  * @return 1
  */
  int AddPassengers(Passenger *);
  /**
  * @brief Update the private list passengers_
  *
  */
  void Update();
  /**
  * @brief Used in the bus to have access to the private member for bus update
  *
  * @return Passenger list in stop class
  */
  std::list<Passenger *> GetPassengers();
  /**
  * @brief Load all passengers to bus / erase elements in passenger list
  *
  */
  void LoadPassenger();
  /**
  * @brief report important information to the ostream
  *
  */
  void Report(std::ostream&) const;
  /**
  * @brief Get Longtitude location of the stop
  *
  * @return double longtitude
  */
  double GetLongitude();
  /**
  * @brief Get latitude location of the stop
  *
  * @return double latitude
  */
  double GetLatitude();

 private:
  int id_;
  std::list<Passenger *> passengers_;  // considered array, vector, queue, list
  /**
  * @brief location at x axis in 2d
  *
  */
  double longitude_;
  /**
  * @brief location at y axis in 2d
  *
  */
  double latitude_;  // are we using long/lat coords?
  // derived information - not needed depending on passengers_
  // data structure implementation?
  // int passengers_present_;
};
#endif  // SRC_STOP_H_
