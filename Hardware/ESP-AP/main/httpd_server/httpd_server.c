//
// Created by fuxin on 11/14/21.
//

#include <esp_log.h>
#include <esp_http_server.h>
#include "httpd_server.h"

const char *TAG_HTTPD = "TAG_HTTPD";

esp_err_t handler_config_sta(httpd_req_t *req) {
    ESP_LOGI(TAG_HTTPD, "handler_config_sta...");
    char *requestData = "";
    int result = httpd_req_recv(req, requestData, req->content_len);
    ESP_LOGI(TAG_HTTPD, "%.*s", result, requestData);
    if (result > 0) {
        ESP_LOGI(TAG_HTTPD, "=========== RECEIVED DATA ==========");
        ESP_LOGI(TAG_HTTPD, "%.*s", result, requestData);
        ESP_LOGI(TAG_HTTPD, "====================================");
    }
    return ESP_OK;
}

void start_httpd() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t handle = NULL;

    ESP_LOGI(TAG_HTTPD, "Starting HTTP server on port: '%d'", config.server_port);

    httpd_uri_t uri_config_sta = {.uri = "/connectWifi", .method = HTTP_POST, .handler = handler_config_sta, .user_ctx = NULL};

    ESP_ERROR_CHECK(httpd_start(&handle, &config));
    ESP_ERROR_CHECK(httpd_register_uri_handler(handle, &uri_config_sta));
}