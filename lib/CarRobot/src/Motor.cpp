#include "Motor.hpp"
#include <Arduino.h>

namespace Robot {

Motor::Motor(int pin1, int pin2) : pin1(pin1), pin2(pin2) { forward(); }

void Motor::forward() {
  isForward = true;
  analogWrite(pin1, 0);
  analogWrite(pin2, speed);
}

void Motor::backward() {
  isForward = false;
  analogWrite(pin1, speed);
  analogWrite(pin2, 0);
}

void Motor::setSpeed(int speed_value) {
  speed = speed_value;
  if (isForward) {
    forward();
  } else {
    backward();
  }
}

Motor::~Motor() {
  analogWrite(pin1, 0);
  analogWrite(pin2, 0);
}

} // namespace Robot
