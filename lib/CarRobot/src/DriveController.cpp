#include "DriveController.hpp"

#include <utility>

namespace Robot {

DriveController::DriveController(Motor &&motor_right, Motor &&motor_left)
    : motorRight(std::move(motor_right)), motorLeft(std::move(motor_left)) {
  lastSpeed = motorLeft.getSpeed();
}

void DriveController::turnRight() {
  motorRight.backward();
  motorLeft.forward();
  restoreSpeed();
}

void DriveController::turnLeft() {
  motorRight.forward();
  motorLeft.backward();
  restoreSpeed();
}

void DriveController::goForward() {
  motorRight.forward();
  motorLeft.forward();
  restoreSpeed();
}

void DriveController::goBackward() {
  motorRight.backward();
  motorLeft.backward();
  restoreSpeed();
}

void DriveController::stop() {
  if (!isStop) {
    lastSpeed = motorLeft.getSpeed();
    isStop = true;
    motorRight.setSpeed(0);
    motorLeft.setSpeed(0);
  }
}

void DriveController::setSpeed(int speedValue) {
  motorRight.setSpeed(speedValue);
  motorLeft.setSpeed(speedValue);
}

void DriveController::restoreSpeed() {
  if (isStop) {
    motorLeft.setSpeed(lastSpeed);
    motorRight.setSpeed(lastSpeed);
    isStop = false;
  }
}

} // namespace Robot
