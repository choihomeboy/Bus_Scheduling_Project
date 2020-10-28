/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <list>
#include <iostream>
#include <string>

#include "src/passenger_generator.h"
#include "src/stop.h"
#include "src/data_structs.h"

class Stop;

class PassengerGenerator;
/**
 * @brief The main class for the acitivity of the route.
 *
 */
class Route {
 public:
   /**
   * @brief Constructs a route with name, stops, distances, the number of stops,
   *                        and passenger generator
   *
   * @param[in] string holding an route name
   * @param[in] stops stops that consist of the route
   * @param[in] distances distances between the stops
   * @param[in] num_stops the number of stops in stops
   * @param[in] PassengerGenerator generator for passengers
   *
   */
  Route(std::string name, Stop ** stops, double * distances, int num_stops,
        PassengerGenerator *);
  /**
  * @brief Copy the same route for easier construction of bus
  *
  * @return cloned route
  */
  Route * Clone();
  /**
  * @brief Used in simulator, update the private list stops_
  *
  */
  void Update(std::ostream& = (std::cout));
  /**
  * @brief report important information related to the route to the ostream
  *
  */
  void Report(std::ostream&);
  /**
  * @brief At the transit of route, distanceleft-=incoming_route first distance
  * @brief used in the bus
  */
  void SetTransitDistance();
  /**
  * @brief Change destination_stop_(approaching stop) to next stop when arrived
  *
  */
  void NextStop();
  /**
  * @brief Check if bus is at the last stop checking if distance_left_<=0
  *
  * @return true when it is at the end of the stop of the route.
  */
  bool IsAtEnd();
  /**
  * @brief Find where to go, used in the bus to track the location of the bus
  *
  * @return Destination stop object
  */
  Stop * GetDestinationStop();
  /**
  * @brief When arrived at stop, bus uses for distance remaining to next stop
  *
  * @return Distance from current stop to next stop
  */
  double GetNextStopDistance();
  /**
  * @brief How far is to the end of the route
  *
  * @return Distance from current stop to the last stop
  */
  double GetDistanceLeft();
  /**
  * @brief Get name of the route
  *
  * @return string name of the route
  */
  std::string GetName();
  /**
  * @brief Get stops used to build the route
  *
  * @return List of stops
  */
  std::list<Stop *> GetStops();
  /**
  * @brief Update the routedata struct to keep up with the newest values
  for simulator
  *
  *
  */
  void UpdateRouteData();
  /**
  * @brief Get RouteData which keeps tracking the route variables
  *
  * @return RouteData struct
  */
  RouteData GetRouteData();

 private:
  /**
  * @brief Generates passengers on its route
  * @brief located in here to create more than once as time increases
  *
  */
  PassengerGenerator * generator_;
  /**
  * @brief Stops in a route cannot be share with the other routes
  *
  */
  std::list<Stop *> stops_;
  /**
  * @brief Distances between the stops for the bus to track how more to go
  * @brief length = num_stops_ - 1
  */
  std::list<double> distances_between_;
  std::string name_;
  /**
  * @brief Number of stops at the route used in initialization and report.
  *
  */
  int num_stops_;
  /**
  * @brief Always starts at zero, used to track where the bus is
  *
  */
  int destination_stop_index_;
  /**
  * @brief The object of the closest stop where the bus is approaching.
  *
  */
  Stop * destination_stop_;
  /**
  * @brief How far left until the end, used to track where the bus is in route.
  *
  */
  double distance_left_;
  // double trip_time_; // derived data - total distance travelled on route
  RouteData route_data_;
};
#endif  // SRC_ROUTE_H_
