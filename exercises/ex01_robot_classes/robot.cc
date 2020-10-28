#include <cmath>
#include <iostream>

#include "robot.h"

void Robot::MoveForward(int distance) {
  position_[0] = position_[0] + distance*cos(direction_angle_);
  position_[1] = position_[1] + distance*sin(direction_angle_);
}

void Robot::Display() {
  std::cout
  << "Pos [" << position_[0] << " " << position_[1] << "]. angle "
  << direction_angle_ << std::endl;
}

// // setters and getters
// void Robot::set_position( int x, int y) {
//   position_[0] = x;
//   position_[1] = y;
// }
// int* Robot::get_position() {
//   return position_;
// }
// void Robot::set_direction_angle_rad(float d) {
//   direction_angle_ = d;
// }
// float Robot::get_direction_angle_rad() {
//   return direction_angle_;
// }
Robot::Robot( int x, int y, float theta ) {
  position_[0] = x;
  position_[1] = y;
  direction_angle_ = theta;
} //Constructor
