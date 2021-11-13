#include <nvs_flash.h>
#include <esp_wifi.h>

#include "wifi_ap/wifi_ap.h"
#include "httpd_server/httpd_server.h"
#include "mqttd_client/mqttd_client.h"

void app_main() {
    tcpip_adapter_init();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    start_ap();
    start_httpd();
    connect_mqtt();
}