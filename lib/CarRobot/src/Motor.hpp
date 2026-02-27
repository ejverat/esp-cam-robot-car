#pragma once

namespace Robot {

class Motor {
public:
  Motor(int pin1, int pin2);
  void forward();
  void backward();
  void setSpeed(int speed_value);
  void increaseSpeed(int value);
  void decreaseSpeed(int value);
  ~Motor();

private:
  int pin1;
  int pin2;
  static constexpr int INITIAL_SPEED = 170;
  int speed = INITIAL_SPEED;
  bool isForward = true;
};
} // namespace Robot
