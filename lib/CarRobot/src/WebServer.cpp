#include "WebServer.hpp"
#include "DriveController.hpp"
#include "RobotGPIO.hpp"
#include "esp32-hal-gpio.h"
#include "esp_http_server.h"
#include <string_view>

namespace Robot {
httpd_handle_t camera_httpd = NULL;
httpd_handle_t stream_httpd = NULL;

esp_err_t index_handler(httpd_req_t *req) {
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)WebServer::INDEX_HTML,
                         strlen(WebServer::INDEX_HTML));
}

esp_err_t action_handler(httpd_req_t *req) {
  char query[100];
  int len = httpd_req_get_url_query_len(req) + 1;

  if (len > sizeof(query)) {
    httpd_resp_send_404(req);
    return ESP_OK;
  }

  if (httpd_req_get_url_query_str(req, query, len) == ESP_OK) {
    std::string_view query_str{query};

    auto mDriverPtr = static_cast<DriveController *>(req->user_ctx);

    if (query_str == "go=forward") {
      mDriverPtr->goForward();
    } else if (query_str == "go=backward") {
      mDriverPtr->goBackward();
    } else if (query_str == "go=left") {
      mDriverPtr->turnLeft();
    } else if (query_str == "go=right") {
      mDriverPtr->turnRight();
    } else if (query_str == "go=stop") {
      mDriverPtr->stop();
    } else if (query_str == "led=on") {
      digitalWrite(GPIO::FLASHLIGHT_PIN, HIGH);
    } else if (query_str == "led=off") {
      digitalWrite(GPIO::FLASHLIGHT_PIN, LOW);
    } else if (query_str == "go=plus") {
      mDriverPtr->increaseSpeed(85);
    } else if (query_str == "go=minus") {
      mDriverPtr->decreaseSpeed(85);
    }
  }

  return httpd_resp_send(req, "", HTTPD_RESP_USE_STRLEN);
}

esp_err_t stream_handler(httpd_req_t *req) {
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)WebServer::INDEX_HTML,
                         strlen(WebServer::INDEX_HTML));
}

WebServer::WebServer(Camera camera, DriveController driver)
    : mCamera(camera), mDriver(driver) {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;
  httpd_uri_t index_uri = {.uri = "/",
                           .method = HTTP_GET,
                           .handler = index_handler,
                           .user_ctx = NULL};

  httpd_uri_t cmd_uri = {.uri = "/action",
                         .method = HTTP_GET,
                         .handler = action_handler,
                         .user_ctx = &mDriver};
  httpd_uri_t stream_uri = {.uri = "/stream",
                            .method = HTTP_GET,
                            .handler = stream_handler,
                            .user_ctx = &mCamera};
  if (httpd_start(&camera_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(camera_httpd, &index_uri);
    httpd_register_uri_handler(camera_httpd, &cmd_uri);
  }
  config.server_port += 1;
  config.ctrl_port += 1;
  if (httpd_start(&stream_httpd, &config) == ESP_OK) {
    httpd_register_uri_handler(stream_httpd, &stream_uri);
  }
}

} // namespace Robot
