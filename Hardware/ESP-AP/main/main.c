#include <string.h>
#include <nvs_flash.h>
#include <esp_wifi.h>
#include <esp_log.h>

static const char *TAG = "EXAMPLE_TAG";
static const char *EXAMPLE_ESP_WIFI_SSID = "ESP8266";
static const char *EXAMPLE_ESP_WIFI_PASS = "Asdf1234";

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    switch (event_id) {
        case WIFI_EVENT_AP_START:
            ESP_LOGI(TAG, "WIFI_EVENT_AP_START %s", event_base);
            break;
        case WIFI_EVENT_AP_STOP:
            ESP_LOGI(TAG, "WIFI_EVENT_AP_STOP %s", event_base);
            break;
        case WIFI_EVENT_AP_STACONNECTED:
            ESP_LOGI(TAG, "WIFI_EVENT_AP_STACONNECTED %s", event_base);
            break;
        case WIFI_EVENT_AP_STADISCONNECTED:
            ESP_LOGI(TAG, "WIFI_EVENT_AP_STADISCONNECTED %s", event_base);
            break;
        default:
            break;
    }
}

static void start_ap() {
    wifi_config_t wifi_config_ap = {.ap = {
            .ssid = {EXAMPLE_ESP_WIFI_SSID},
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .password = {EXAMPLE_ESP_WIFI_PASS},
            .max_connection = 10,
            .authmode = WIFI_AUTH_WPA2_WPA3_PSK
    }};

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    // setting Wi-Fi AP info
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config_ap));
    // register Wi-Fi event handler
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    // set Wi-Fi mode to AP mode
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    // start Wi-Fi
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "start ap...");
}

void app_main() {
    ESP_ERROR_CHECK(nvs_flash_init());
    start_ap();
}