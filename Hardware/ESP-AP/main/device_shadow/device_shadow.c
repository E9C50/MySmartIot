//
// Created by fuxin on 11/14/21.
//
#include <cJSON.h>
#include "device_shadow.h"
#include "../board_led/board_led.h"
#include "../mqttd_client/mqttd_client.h"

void publish_device_shadow() {
    cJSON *root = cJSON_CreateObject();
    cJSON *reported = cJSON_CreateObject();

    cJSON_AddItemToObject(root, "reported", reported);
    cJSON_AddItemToObject(reported, "esp-led", cJSON_CreateNumber(BOARD_LED_STATUS));
    cJSON_AddItemToObject(reported, "bedroom-light", cJSON_CreateNumber(1));

    publish_message(cJSON_Print(root));
    if (root) {
        cJSON_Delete(root);
    }
}