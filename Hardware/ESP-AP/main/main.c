#include <nvs_flash.h>
#include <esp_wifi.h>
#include <driver/gpio.h>

#include "wifi_ap/wifi_ap.h"
#include "wifi_sta/wifi_sta.h"
#include "mqttd_client/mqttd_client.h"

#define GPIO_LED_NUM 2

void app_main() {
    tcpip_adapter_init();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    gpio_config_t gpio_config_structure;
    gpio_config_structure.pin_bit_mask = (1ULL << GPIO_LED_NUM);
    gpio_config_structure.mode = GPIO_MODE_OUTPUT;
    gpio_config_structure.pull_up_en = 0;
    gpio_config_structure.pull_down_en = 0;
    gpio_config_structure.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpio_config_structure);
    gpio_set_level(GPIO_LED_NUM, 1);

//    start_ap();
    connect_wifi("RT-AX86U1", "ziru285@room501");
    gpio_set_level(GPIO_LED_NUM, 0);
    connect_mqtt();
}