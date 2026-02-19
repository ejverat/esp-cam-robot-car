#include "Camera.hpp"
#include "Arduino.h"
#include "RobotGPIO.hpp"
#include "esp_camera.h"

namespace Robot {
Camera::Camera(bool videoFlip) {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = GPIO::Y2_GPIO_NUM;
  config.pin_d1 = GPIO::Y3_GPIO_NUM;
  config.pin_d2 = GPIO::Y4_GPIO_NUM;
  config.pin_d3 = GPIO::Y5_GPIO_NUM;
  config.pin_d4 = GPIO::Y6_GPIO_NUM;
  config.pin_d5 = GPIO::Y7_GPIO_NUM;
  config.pin_d6 = GPIO::Y8_GPIO_NUM;
  config.pin_d7 = GPIO::Y9_GPIO_NUM;
  config.pin_xclk = GPIO::XCLK_GPIO_NUM;
  config.pin_pclk = GPIO::PCLK_GPIO_NUM;
  config.pin_vsync = GPIO::VSYNC_GPIO_NUM;
  config.pin_href = GPIO::HREF_GPIO_NUM;
  config.pin_sccb_sda = GPIO::SIOD_GPIO_NUM;
  config.pin_sccb_scl = GPIO::SIOC_GPIO_NUM;
  config.pin_pwdn = GPIO::PWDN_GPIO_NUM;
  config.pin_reset = GPIO::RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_VGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_HVGA;
  }

  esp_err_t err_init = esp_camera_init(&config);

  if (err_init != ESP_OK) {
    // insert error handling here
    Serial.printf("ERROR on camera initialization: 0x%x\n", err_init);
  }

  if (videoFlip) {
    sensor_t *s = esp_camera_sensor_get();
    s->set_framesize(s, FRAMESIZE_VGA);

    s->set_vflip(s, 1);
    s->set_hmirror(s, 0);
  }
}
} // namespace Robot
