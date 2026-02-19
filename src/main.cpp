#include "Camera.hpp"
#include "RobotGPIO.hpp"
#include "soc/rtc_cntl_reg.h" // Used to disable brownout detection for ESP32
#include "soc/soc.h"          // Used to disable brownout detection for ESP32
#include <Arduino.h>
#include <WiFi.h>
#include <memory>

std::shared_ptr<Robot::Camera> pCamera;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector
  //
  //
  Serial.begin(9600);
  Serial.setDebugOutput(false);

  Serial.println("Configuring IO");
  Robot::GPIO::initializePins();

  Serial.println("Initializing camera...");
  pCamera = std::make_shared<Robot::Camera>(false);

  Serial.println("Initializing WiFi");
  WiFi.begin("FamVeraCen", "FamVeraCen_2019");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  Serial.print("IP:");
  Serial.println(WiFi.localIP());
}

void loop() {}
