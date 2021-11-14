#include <nvs_flash.h>
#include <esp_wifi.h>

#include "wifi_ap/wifi_ap.h"
#include "wifi_sta/wifi_sta.h"
#include "board_led/board_led.h"
#include "mqttd_client/mqttd_client.h"

void app_main() {
    initializeBoardLed();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

//    start_ap();
    connect_wifi("RT-AX86U", "ziru285@room501");
    connect_mqtt();
}