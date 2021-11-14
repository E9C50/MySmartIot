//
// Created by fuxin on 11/14/21.
//
#include <string.h>
#include <esp_log.h>
#include "command_handler.h"
#include "../board_led/board_led.h"

const char *TAG_COMMAND = "TAG_COMMAND";

void handler_mqtt_command(const char *command) {
    if (strcmp(command, "OPENLED") == 0) {
        boardLedOpen();
    } else if (strcmp(command, "CLOSELED") == 0) {
        boardLedClose();
    } else {
        ESP_LOGI(TAG_COMMAND, "ERROR COMMAND [%s]", command);
    }
}