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

private:
  Motor motorRight;
  Motor motorLeft;
};
} // namespace Robot
