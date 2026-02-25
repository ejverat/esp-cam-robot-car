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

void Motor::increaseSpeed(int value) {
  if (speed + value >= 255) {
    speed = 255;
  } else {
    speed += value;
  }

  setSpeed(speed);
}

void Motor::decreaseSpeed(int value) {
  if (speed > value) {
    speed -= value;
  } else {
    speed = 0;
  }

  setSpeed(speed);
}

Motor::~Motor() {
  analogWrite(pin1, 0);
  analogWrite(pin2, 0);
}

} // namespace Robot
