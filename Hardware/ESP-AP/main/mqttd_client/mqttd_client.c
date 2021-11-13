//
// Created by fuxin on 11/14/21.
//

#include <esp_log.h>
#include <mqtt_client.h>
#include "mqttd_client.h"

const char *TAG_MQTT = "TAG_MQTT";

esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event) {
    switch (event->event_id) {

        case MQTT_EVENT_BEFORE_CONNECT:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT ready connect.");
            break;
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT is connected.");
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT is disconnected.");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT subscribe topic. [%d - %s]", event->msg_id, event->topic);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT unsubscribe topic. [%d - %s]", event->msg_id, event->topic);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT published message. [%d - %s]", event->msg_id, event->topic);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT received message: [%d - %s]", event->msg_id, event->topic);
            ESP_LOGI(TAG_MQTT, "topic data: [%.*s]", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG_MQTT, "MQTT_EVENT_ERROR: %s", event->data);
            break;
        case MQTT_EVENT_ANY:
            break;
    }
    return ESP_OK;
}

void connect_mqtt() {
    esp_mqtt_client_config_t mqtt_cfg = {
            .uri = MQTT_SERVER,
            .client_id = MQTT_CLIENT_ID,
            .username = MQTT_USERNAME,
            .password = MQTT_PASSWORD,
            .event_handle = mqtt_event_handler
    };
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}