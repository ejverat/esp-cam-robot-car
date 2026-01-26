#include "DriveController.hpp"

#include <utility>

namespace Robot {

DriveController::DriveController(Motor &&motor_right, Motor &&motor_left)
    : motorRight(std::move(motor_right)), motorLeft(std::move(motor_left)) {}

void DriveController::turnRight() {
  motorRight.backward();
  motorLeft.forward();
}

void DriveController::turnLeft() {
  motorRight.forward();
  motorLeft.backward();
}

void DriveController::goForward() {
  motorRight.forward();
  motorLeft.forward();
}

void DriveController::goBackward() {
  motorRight.backward();
  motorLeft.backward();
}

void DriveController::stop() {
  motorRight.setSpeed(0);
  motorLeft.setSpeed(0);
}

void DriveController::setSpeed(int speedValue) {
  motorRight.setSpeed(speedValue);
  motorLeft.setSpeed(speedValue);
}

} // namespace Robot
