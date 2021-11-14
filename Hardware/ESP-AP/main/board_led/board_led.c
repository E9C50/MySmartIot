//
// Created by fuxin on 11/14/21.
//
#include <driver/gpio.h>
#include "board_led.h"

static int BOARD_LED_STATUS = 0;

void initializeBoardLed() {
    gpio_config_t gpio_config_structure;
    gpio_config_structure.pin_bit_mask = (1ULL << GPIO_LED_NUM);
    gpio_config_structure.mode = GPIO_MODE_OUTPUT;
    gpio_config_structure.pull_up_en = 0;
    gpio_config_structure.pull_down_en = 0;
    gpio_config_structure.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio_config_structure);
    boardLedClose();
}

void boardLedOpen() {
    gpio_set_level(GPIO_LED_NUM, 0);
    BOARD_LED_STATUS = 1;
}

void boardLedClose() {
    gpio_set_level(GPIO_LED_NUM, 1);
    BOARD_LED_STATUS = 0;
}