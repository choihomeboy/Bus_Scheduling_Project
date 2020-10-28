// Copyright 2019 Kevin Wendt

#include "src/passenger.h"

#include <iostream>
#include <string>


int Passenger::count_ = 0;

Passenger::Passenger(int destination_stop_id, std::string name): name_(name),
                    destination_stop_id_(destination_stop_id), wait_at_stop_(0),
                    time_on_bus_(0), id_(count_), on_bus_(false) {
  count_++;
}

void Passenger::Update() {
  if (time_on_bus_ >= 1) {
    time_on_bus_++;
  } else if (on_bus_ == true) {
    time_on_bus_++;
  } else if (time_on_bus_ == 0) {
    wait_at_stop_++;
  }
}

void Passenger::GetOnBus() {
  if (time_on_bus_ == 0) {
    on_bus_ = true;
  } else {
    std::cout << "error" << std::endl;
  }
}

int Passenger::GetTotalWait() const {
  return wait_at_stop_ + time_on_bus_;
}

bool Passenger::IsOnBus() const {
  return on_bus_;
}

int Passenger::GetDestination() const {
  return destination_stop_id_;
}

void Passenger::Report(std::ostream &out) const {
  out << "Name: " << name_ << std::endl;
  out << "Destination: " << destination_stop_id_ << std::endl;
  out << "Total Wait: " << GetTotalWait() << std::endl;
  out << "\tWait at Stop: " << wait_at_stop_ << std::endl;
  out << "\tTime on bus: " << time_on_bus_ << std::endl;
}
