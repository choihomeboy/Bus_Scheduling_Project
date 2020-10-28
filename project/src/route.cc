// Copyright 2019 Kevin Wendt

#include "src/route.h"
#include <fstream>
Route::Route(std::string name, Stop ** stops, double * distances,
             int num_stops, PassengerGenerator * psg) {
  num_stops_ = num_stops;
  generator_ = psg;
  for (int i = 0; i < num_stops; i++) {
    stops_.push_back(stops[i]);
  }
  for (int i = 0; i < num_stops - 1; i++) {
    distances_between_.push_back(distances[i]);
    distance_left_ += distances[i];
  }
  name_ = name;
  destination_stop_ = *stops_.begin();
  destination_stop_index_ = 0;
  // route_data_ = RouteData();
  UpdateRouteData();
}

Route* Route::Clone() {
  Stop ** temp_stop = new Stop *[num_stops_];
  int i = 0;
  for (std::list<Stop *>::iterator it=stops_.begin(); it != stops_.end();
                                                                  it++) {
    temp_stop[i] = *it;
    i++;
  }
  i = 0;
  double * temp_distance = new double[num_stops_-1];
  for (std::list<double>::iterator it = distances_between_.begin();
                            it != distances_between_.end(); it++) {
    temp_distance[i] = *it;
    i++;
  }
  Route* temp_route = new Route(name_, temp_stop, temp_distance,
                                        num_stops_, generator_);
  return temp_route;
}

void Route::SetTransitDistance() {
  std::list<double>::iterator it = distances_between_.begin();
  distance_left_ -= *it;
}

bool Route::IsAtEnd() {
  if (distance_left_ <= 0) {    // when the route ends
    return true;
  }
  std::list<double>::iterator it = distances_between_.begin();
  std::advance(it, destination_stop_index_);    // distance between at index
  distance_left_ -= *it;      // update the distance_left_
  return false;
}
double Route::GetDistanceLeft() {
  return distance_left_;
}
void Route::NextStop() {
  destination_stop_index_ += 1;
  std::list<Stop *>::iterator its = stops_.begin();
  std::advance(its, destination_stop_index_);   // get stop at current index
  destination_stop_ = *its;       // update destination stop
}

Stop * Route::GetDestinationStop() {
  return destination_stop_;
}

double Route::GetNextStopDistance() {
  std::list<double>::iterator it = distances_between_.begin();
  std::advance(it, destination_stop_index_-1);
  // because size of distance_between is 1 less so index -1
  return *it;
}
void Route::Update(std::ostream& out) {
  generator_->GeneratePassengers(out);
  // Generate the passenger everytime simulator calls the update
  for (std::list<Stop *>::iterator it = stops_.begin();
    it != stops_.end(); it++) {
    (*it)->Update();
  }
  UpdateRouteData();
}

void Route::Report(std::ostream& out) {
  out << "Name: " << name_ << std::endl;
  out << "Num stops: " << num_stops_ << std::endl;
  out << "        vvvvv Next Stop vvvvv" << std::endl;
  int stop_counter = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
      it != stops_.end(); it++) {
    (*it)->Report(out);
    stop_counter++;
  }
}

std::string Route::GetName() {
  return name_;
}
std::list<Stop *> Route::GetStops() {
  return stops_;
}
void Route::UpdateRouteData() {
  route_data_.id = name_;
  StopData temp = StopData();
  std::vector<StopData> temp_stop;
  // std::vector<StopData> temp;
  for (std::list<Stop *>::iterator it = stops_.begin();
                            it != stops_.end(); it++) {
    temp.id = std::to_string((*it)->GetId());
    temp.position.x = (*it)->GetLongitude();
    temp.position.y = (*it)->GetLatitude();
    temp_stop.push_back(temp);
  }
  route_data_.stops = temp_stop;
}
RouteData Route::GetRouteData() {
  return route_data_;
}
