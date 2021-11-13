//
// Created by fuxin on 11/14/21.
//

#include <string.h>
#include <esp_log.h>
#include <esp_wifi.h>
#include <event_groups.h>
#include "wifi_sta.h"

int retry_num = 0;
const char *TAG_WIFI_STA = "TAG_WIFI_STA";
EventGroupHandle_t wifi_event_group_handler;

void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    if (event_base == WIFI_EVENT) {
        if (event_id == WIFI_EVENT_STA_START) {
            esp_wifi_connect();
        } else if (event_id == WIFI_EVENT_STA_DISCONNECTED) {
            retry_num++;
            esp_wifi_connect();
            ESP_LOGI(TAG_WIFI_STA, "Retry to connect to the AP %d times.", retry_num);
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        ESP_LOGI(TAG_WIFI_STA, "Got IP: %s", ip4addr_ntoa(&event->ip_info.ip));
        xEventGroupSetBits(wifi_event_group_handler, WIFI_CONNECTED_BIT);
        retry_num = 0;
    }
}

int connect_wifi(const char *wifiSsidStr, const char *wifiPassStr) {
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL));

    wifi_config_t wifi_config = {};
    memcpy(wifi_config.sta.ssid, wifiSsidStr, sizeof(wifi_config.sta.ssid));
    memcpy(wifi_config.sta.password, wifiPassStr, sizeof(wifi_config.sta.password));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG_WIFI_STA, "Wifi_init_sta finished.");

    wifi_event_group_handler = xEventGroupCreate();
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group_handler, WIFI_CONNECTED_BIT,
                                           pdFALSE, pdFALSE, portMAX_DELAY);

    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler));
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler));
    vEventGroupDelete(wifi_event_group_handler);

    /* 根据事件标志组等待函数的返回值获取WiFi连接状态 */
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG_WIFI_STA, "connected to ap SSID:%s", wifiSsidStr);
        return 1;
    } else {
        ESP_LOGI(TAG_WIFI_STA, "connect timeout SSID:%s", wifiSsidStr);
        return 0;
    }
}