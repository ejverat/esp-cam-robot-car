#pragma once

#include "Motor.hpp"

namespace Robot {
class DriveController {
public:
  DriveController(Motor &&motor_right, Motor &&motor_left);
  void turnRight(void);
  void turnLeft(void);
  void goForward(void);
  void goBackward(void);
  void stop(void);
  void setSpeed(int speedValue);

  inline void increaseSpeed(int value) {
    motorLeft.increaseSpeed(value);
    motorRight.increaseSpeed(value);
    lastSpeed = motorLeft.getSpeed();
  }

  inline void decreaseSpeed(int value) {
    motorLeft.decreaseSpeed(value);
    motorRight.decreaseSpeed(value);
    lastSpeed = motorLeft.getSpeed();
  }

private:
  Motor motorRight;
  Motor motorLeft;
  bool isStop = true;
  int lastSpeed;

  void restoreSpeed();
};
} // namespace Robot
