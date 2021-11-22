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
    cJSON_AddNumberToObject(reported, "esp-led", BOARD_LED_STATUS);
    cJSON_AddNumberToObject(reported, "bedroom-light", BOARD_LED_STATUS);
    cJSON_AddItemToObject(root, "reported", reported);
//    char *json = cJSON_Print(root);
    char *json = cJSON_PrintUnformatted(root);
    publish_message(json);

    if (root) {
        cJSON_Delete(root);
    }
    if (json) {
        cJSON_free(json);
    }
}