// Copyright 2019 Kevin Wendt

/*******************************************************************************
  * Includes
******************************************************************************/
#include "src/bus.h"
#include <fstream>

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

Bus::Bus(std::string name, Route * out, Route * in,
                        int capacity, double speed) {
  // initialization
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  which_route_ = 1;
  next_stop_ = outgoing_route_->GetDestinationStop();
  previous_stop_ = outgoing_route_->GetDestinationStop();

  distance_remaining_ = 0;
  current_route_ = outgoing_route_;
  // bus_data_= BusData();
  UpdateBusData();
}


bool Bus::LoadPassenger(Passenger * new_passenger) {
  int num_passengers = passengers_.size();
  if (num_passengers < passenger_max_capacity_) {  // check passenger capaicty
    passengers_.push_back(new_passenger);   // add passenger to bus passengers
    return true;  // done
  } else {
    std::cout << "Bus is full now" << std::endl;
    return false;
  }  // fail
}

bool Bus::UnloadPassenger(int idx) {
  // delete passenger from the list
  std::list<Passenger *>::iterator it = passengers_.begin();
  std::advance(it, idx);
  passengers_.erase(it);
  return true;
}

bool Bus::Move() {
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {  // 1 clock passes -> passenger update
    (*it)->Update();
  }
  // distance_remaining_ = distance_remaining_ - speed_;  // distance update
  return true;
}

// bool Refuel() {
//  This may become more complex in the future
//  fuel_ = max_fuel_;
// }

void Bus::Update() {  // using common Update format
  if (which_route_ == 3) {  // when bus has no more route to move
    return;   // do nothing
  }
  int pass_size = passengers_.size();
  if (distance_remaining_ <= speed_) {  // check if arrived
    int pass_idx = pass_size-1;
    for (std::list<Passenger *>::reverse_iterator it = passengers_.rbegin();
                                    it != passengers_.rend(); it++) {
      if ((*it)->GetDestination() == next_stop_->GetId()) {
        // passenger arrived
        UnloadPassenger(pass_idx);               // Unload arrived passengers
      }
      pass_idx--;
    }
    std::list<Passenger *> pass = next_stop_->GetPassengers();
    for (std::list<Passenger *>::iterator it = pass.begin();
                                it != pass.end(); it++) {
      LoadPassenger(*it);                   // Load all passengers to the bus
    }
    next_stop_->LoadPassenger();        // Clear the stop

    if (current_route_->IsAtEnd() == true) {
      if (which_route_ == 1) {
        which_route_ = 2;
        next_stop_ = current_route_->GetDestinationStop();
        std::list<Passenger *> pass_incoming = next_stop_->GetPassengers();
        for (std::list<Passenger *>::iterator it = pass_incoming.begin();
                                      it != pass_incoming.end(); it++) {
          LoadPassenger(*it);            // Load all passengers to the bus
        }
        next_stop_->LoadPassenger();
        current_route_ = incoming_route_;

        current_route_->SetTransitDistance();

        previous_stop_ = current_route_->GetDestinationStop();

        current_route_->NextStop();
        next_stop_ = current_route_->GetDestinationStop();
        distance_remaining_ = current_route_->GetNextStopDistance();
      } else if (which_route_ == 2) {
        // Bus has to be deleted
        which_route_ = 3;
        std::cout << "END this bus" << std::endl;
      }
    } else {  // current route is not at the end
      previous_stop_ = current_route_->GetDestinationStop();
      // update the destination stop
      current_route_->NextStop();
      next_stop_ = current_route_->GetDestinationStop();
      // update the distance_remaining_
      distance_remaining_ = current_route_->GetNextStopDistance();
    }
    Move();                 // bus passengers update
  } else {
    Move();                 // bus passengers update
    distance_remaining_ = distance_remaining_ - speed_;  // distance update
  }
  UpdateBusData();
}

void Bus::Report(std::ostream &out) {
  out << "Name: " << name_ << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Next stop: " << next_stop_->GetId() << std::endl;
  out << "Distance to next stop: " << distance_remaining_ << std::endl;
  out << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}

std::list<Passenger *> Bus::GetPassengers() {
  return passengers_;
}

void Bus::UpdateBusData() {
  bus_data_.id = name_;
  bus_data_.position.x = next_stop_->GetLongitude();
  bus_data_.position.y = next_stop_->GetLatitude();
  int temp = passengers_.size();
  bus_data_.num_passengers =  temp;
  bus_data_.capacity = passenger_max_capacity_;
}
BusData Bus::GetBusData() {
  return bus_data_;
}
std::string Bus::GetName() const {
  return name_;
}
Stop * Bus::GetNextStop() {
  return next_stop_;
}
size_t Bus::GetNumPassengers() {
  return passengers_.size();
}
int Bus::GetCapacity() {
  return passenger_max_capacity_;
}

bool Bus::IsTripComplete() {
  if (which_route_ == 3) {
    return true;
  } else {
    return false;
  }
}
