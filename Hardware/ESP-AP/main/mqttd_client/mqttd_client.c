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
            printf("MQTT_client ready cnnnect to EMQ. \n");
            break;
        case MQTT_EVENT_CONNECTED:
            printf("MQTT_client cnnnect to EMQ ok. \n");
            break;
        case MQTT_EVENT_DISCONNECTED:
            printf("MQTT_client have disconnected. \n");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            printf("mqtt subscribe ok. msg_id = %d \n", event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            printf("mqtt unsubscribe ok. msg_id = %d \n", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            printf("mqtt published ok. msg_id = %d \n", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            printf("mqtt received topic: %.*s \n", event->topic_len, event->topic);
            printf("topic data: [%.*s]\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            printf("MQTT_EVENT_ERROR \n");
            break;
        case MQTT_EVENT_ANY:
            break;
    }
    return ESP_OK;
}

void connect_mqtt() {
    ESP_LOGI(TAG_MQTT, "starting mqtt...");
    esp_mqtt_client_config_t mqtt_cfg = {
            .uri = MQTT_SERVER,
            .client_id = MQTT_CLIENT_ID,
            .username = MQTT_USERNAME,
            .password = MQTT_PASSWORD,
            .event_handle = mqtt_event_handler
    };
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
    ESP_LOGI(TAG_MQTT, "started mqtt.");
}