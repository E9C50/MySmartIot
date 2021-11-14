//
// Created by fuxin on 11/14/21.
//
#include <string.h>
#include <esp_log.h>
#include <esp_wifi.h>

#include "wifi_ap.h"
#include "../httpd_server/httpd_server.h"

const char *TAG_WIFI_AP = "TAG_WIFI_AP";

void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    switch (event_id) {
        case WIFI_EVENT_AP_START:
            ESP_LOGI(TAG_WIFI_AP, "WIFI_EVENT_AP_START %s", event_base);
            break;
        case WIFI_EVENT_AP_STOP:
            ESP_LOGI(TAG_WIFI_AP, "WIFI_EVENT_AP_STOP %s", event_base);
            break;
        case WIFI_EVENT_AP_STACONNECTED:
            ESP_LOGI(TAG_WIFI_AP, "WIFI_EVENT_AP_STACONNECTED %s", event_base);
            break;
        case WIFI_EVENT_AP_STADISCONNECTED:
            ESP_LOGI(TAG_WIFI_AP, "WIFI_EVENT_AP_STADISCONNECTED %s", event_base);
            break;
        default:
            break;
    }
}

void start_ap() {
    ESP_LOGI(TAG_WIFI_AP, "starting ap...");
    wifi_config_t wifi_config_ap = {.ap = {
            .ssid = AP_ESP_WIFI_SSID,
            .ssid_len = strlen(AP_ESP_WIFI_SSID),
            .password = AP_ESP_WIFI_PASS,
            .max_connection = AP_ESP_WIFI_MAX_CONN,
            .authmode = AP_ESP_WIFI_AUTH
    }};

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config_ap));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG_WIFI_AP, "started ap.");

    start_httpd();
}