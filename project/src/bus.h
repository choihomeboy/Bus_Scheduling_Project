/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */


#ifndef SRC_BUS_H_
#define SRC_BUS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <iostream>
#include <list>
#include <string>

#include "src/passenger.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/data_structs.h"

class PassengerUnloader;
class PassengerLoader;
class Route;
class Stop;
/**
 * @brief The main class for the acitivity of the bus.
 *
 */
class Bus {
 public:
 /**
 * @brief Constructs a bus with name, routes, capacity, and speed
 *
 *
 * @param[in] name string holding an bus name
 * @param[in] out the first route that is used by bus
 * @param[in] in the second route that is used by bus
 * @param[in] capacity the number of passengers that bus can take
 * @param[in] spped how far the bus travels in one timestep
 *
 */
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                                                 double speed = 1);
 /**
 * @brief Load all the passengers if condition of max capacity is met
 *
 * @return true for success
 */
  bool LoadPassenger(Passenger *);  // returning revenue delta
  /**
  * @brief Erase the arriving passengers from the passenger lists
  * @brief Tracking the index of the passengers in the list
  *
  * @return true when it is successful
  */
  bool UnloadPassenger(int);
  /**
  * @brief Updates the passengers in the list
  *
  * @return true when it is successful
  */
  bool Move();
  /**
  * @brief Handles unload, load, move, distance update and route update
  *
  */
  void Update();
  /**
  * @brief Report important information of bus class
  *
  */
  void Report(std::ostream &out);
  /**
  * @brief Updates the passengers in the list
  *
  * @return true when it is successful
  */
  std::list<Passenger *> GetPassengers();
  /**
  * @brief Updates the passengers in the list
  *
  * @return true when it is successful
  */
  void UpdateBusData();
  /**
  * @brief Get BusData struct for simulator
  *
  * @return BusData struct
  */
  BusData GetBusData();
  /**
  * @brief Get name of the bus
  *
  * @return string name of the bus
  */
  std::string GetName() const;
  /**
  * @brief Get next stop that bus is reaching to
  *
  * @return stop that the bus is reaching to
  */
  Stop * GetNextStop();
  /**
  * @brief Get current number of passengers in the bus
  *
  * @return size_t number of passengers in the bus
  */
  size_t GetNumPassengers();
  /**
  * @brief Get hom many passengers max the bus can take
  *
  * @return integer capacity of the bus
  */
  int GetCapacity();
  /**
  * @brief Check if the bus has finished the trip on both routes.
  *
  * @return true if no more route to drive on
  */
  bool IsTripComplete();

 private:
   /**
   * @brief List of passengers who are riding in the bus
   *
   */
  std::list<Passenger *> passengers_;
  /**
  * @brief Maximum capacity that the bus can handle at a time
  *
  */
  int passenger_max_capacity_;
  /**
  * @brief Track if the bus is finished both outgoing route and incoming route
  *
  */
  int which_route_;
  std::string name_;
  /**
  * @brief could also be called "distance travelled in one time step
  *
  */
  double speed_;
  Route * outgoing_route_;
  Route * incoming_route_;
  /**
  * @brief Track if it is on outgoing route, incoming route
  *
  */
  Route * current_route_;
  /**
  * @brief When negative, unload/load procedure occurs
  *
  */
  double distance_remaining_;
  /**
  * @brief Track the approaching stop
  *
  */
  Stop * next_stop_;
  Stop * previous_stop_;
  // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
  BusData bus_data_;
};
#endif  // SRC_BUS_H_
