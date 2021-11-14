//
// Created by fuxin on 11/14/21.
//

#define MQTT_SERVER  "mqtt://3C6LX6DIXP.iotcloud.tencentdevices.com"
#define MQTT_USERNAME "3C6LX6DIXPNodeMCU-8266;12010126;ZKREJ;1672239330"
#define MQTT_PASSWORD "59eb0420ef86c1fc383a23da8133e3df23cafff13e87e80e58a1938e000c1c0e;hmacsha256"
#define MQTT_CLIENT_ID "3C6LX6DIXPNodeMCU-8266"
#define MQTT_SUB_TOPIC "3C6LX6DIXP/NodeMCU-8266/sub"
#define MQTT_PUB_TOPIC "3C6LX6DIXP/NodeMCU-8266/pub"

void connect_mqtt();

void publish_message(const char *message);