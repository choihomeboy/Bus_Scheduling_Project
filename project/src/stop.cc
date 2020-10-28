// Copyright 2019 Kevin Wendt

#include <iostream>
#include <vector>
#include <fstream>
#include "src/stop.h"

Stop::Stop(int id, double longitude,
           double latitude) : id_(id), longitude_(longitude),
            latitude_(latitude) {  // Defaults to Westbound Coffman Union stop
  // no initialization of list of passengers necessary
}

int Stop::AddPassengers(Passenger * pass) {
  passengers_.push_back(pass);
  return 1;
}

void Stop::Update() {
  if (!passengers_.empty()) {
    for (std::list<Passenger *>::iterator it = passengers_.begin();
         it != passengers_.end(); it++) {
      (*it)->Update();
    }
  }
}

void Stop::LoadPassenger() {
  for (std::list<Passenger *>::iterator it = passengers_.begin();
  it != passengers_.end(); it++) {
    (*it)->GetOnBus();
  }
  passengers_.clear();
}

std::list<Passenger *> Stop::GetPassengers() {
  return passengers_;
}

int Stop::GetId() const {
  return id_;
}

void Stop::Report(std::ostream& out) const {
  out << "ID: " << id_ << std::endl;
  out << "Passengers waiting: " << passengers_.size() << std::endl;
  for (std::list<Passenger *>::const_iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    (*it)->Report(out);
  }
}

double Stop::GetLongitude() {
  return longitude_;
}
double Stop::GetLatitude() {
  return latitude_;
}
