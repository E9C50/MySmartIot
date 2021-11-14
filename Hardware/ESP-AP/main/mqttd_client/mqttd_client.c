//
// Created by fuxin on 11/14/21.
//

#include <esp_log.h>
#include <mqtt_client.h>
#include "mqttd_client.h"
#include "../command_handler/command_handler.h"

const char *TAG_MQTT = "TAG_MQTT";
esp_mqtt_client_handle_t client;

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event) {
    char mag_data[100];
    esp_mqtt_client_handle_t client = event->client;
    switch (event->event_id) {
        case MQTT_EVENT_BEFORE_CONNECT:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT ready connect.");
            break;
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT is connected. Now subscribe topic [%s]...", MQTT_SUB_TOPIC);
            esp_mqtt_client_subscribe(client, MQTT_SUB_TOPIC, 0);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT is disconnected.");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT subscribe topic.");
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT unsubscribe topic.");
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT published message.");
            break;
        case MQTT_EVENT_DATA:
            sprintf(mag_data, "%.*s", event->data_len, event->data);
            ESP_LOGI(TAG_MQTT, "MQTT_CLIENT received message: %.*s", event->topic_len, event->topic);
            ESP_LOGI(TAG_MQTT, "topic data: %.*s", event->data_len, mag_data);
            handler_mqtt_command(mag_data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG_MQTT, "MQTT_EVENT_ERROR");
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
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}

void publish_message(const char *message) {
//    ESP_LOGI(TAG_MQTT, "MQTT_PUBLISH_MESSAGE : %s", message);
    esp_mqtt_client_publish(client, MQTT_PUB_TOPIC, message, 0, 1, 0);
}