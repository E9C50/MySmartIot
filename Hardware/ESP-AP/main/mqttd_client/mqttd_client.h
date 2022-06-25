//
// Created by fuxin on 11/14/21.
//

#define MQTT_SERVER  "mqtt://mqtt-server.fxxlxy.com"
#define MQTT_USERNAME "MYSMARTIOT"
#define MQTT_PASSWORD "jasonFX3A87WLQ"
#define MQTT_CLIENT_ID "SmartIot-NodeMCU-8266"
#define MQTT_SUB_TOPIC "smart-iot/device/esp/command"
#define MQTT_PUB_TOPIC "smart-iot/device/esp/report"

void connect_mqtt();


void publish_message(const char *message);