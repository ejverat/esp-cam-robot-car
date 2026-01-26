#include "RobotGPIO.hpp"
#include <Arduino.h>

namespace Robot::GPIO {
void initializePins(void) {
  pinMode(FLASHLIGHT_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_CONTROL_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_CONTROL_PIN2, OUTPUT);
  pinMode(LEFT_MOTOR_CONTROL_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_CONTROL_PIN2, OUTPUT);
}
} // namespace Robot::GPIO
