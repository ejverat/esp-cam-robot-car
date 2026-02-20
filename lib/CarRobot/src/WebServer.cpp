#include "WebServer.hpp"
#include "DriveController.hpp"
#include "esp_http_server.h"

namespace Robot {
httpd_handle_t camera_httpd = NULL;
httpd_handle_t stream_httpd = NULL;

esp_err_t index_handler(httpd_req_t *req) {
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)WebServer::INDEX_HTML,
                         strlen(WebServer::INDEX_HTML));
}

esp_err_t action_handler(httpd_req_t *req) {
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, (const char *)WebServer::INDEX_HTML,
                         strlen(WebServer::INDEX_HTML));
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
                         .user_ctx = NULL};
  httpd_uri_t stream_uri = {.uri = "/stream",
                            .method = HTTP_GET,
                            .handler = stream_handler,
                            .user_ctx = NULL};
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
