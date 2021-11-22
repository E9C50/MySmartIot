#include <nvs_flash.h>
#include <esp_timer.h>
#include <esp_wifi.h>

#include "wifi_ap/wifi_ap.h"
#include "wifi_sta/wifi_sta.h"
#include "board_led/board_led.h"
#include "mqttd_client/mqttd_client.h"
#include "device_shadow/device_shadow.h"

void timer_tick_loop(void *arg) {
    publish_device_shadow();
}

void app_main() {
    esp_timer_init();
    initializeBoardLed();
    tcpip_adapter_init();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

//    start_ap();
    connect_wifi("RT-AX86U", "ziru285@room501");
    connect_mqtt();

    esp_timer_handle_t test_p_handle = 0;
    esp_timer_create_args_t test_periodic_arg = {.callback = &timer_tick_loop};
    esp_timer_create(&test_periodic_arg, &test_p_handle);
    esp_timer_start_periodic(test_p_handle, 1 * 1000 * 1000);
}