#include <string.h>
#include <nvs_flash.h>
#include <esp_wifi.h>
#include <esp_log.h>
#include <esp_http_server.h>

#define AP_ESP_WIFI_MAX_CONN 10
#define AP_ESP_WIFI_SSID "ESP8266"
#define AP_ESP_WIFI_PASS "Asdf1234"
#define AP_ESP_WIFI_AUTH WIFI_AUTH_WPA_PSK

static const char *TAG = "EXAMPLE_TAG";

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
            .ssid = AP_ESP_WIFI_SSID,
            .ssid_len = strlen(AP_ESP_WIFI_SSID),
            .password = AP_ESP_WIFI_PASS,
            .max_connection = AP_ESP_WIFI_MAX_CONN,
            .authmode = AP_ESP_WIFI_AUTH
    }};

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config_ap));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_LOGI(TAG, "start ap...");
}

static void start_httpd() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t handle = NULL;
    if (httpd_start(&handle, &config) == ESP_OK) {
        httpd_uri_t uri_connect_wifi;
        httpd_register_uri_handler(handle, &uri_connect_wifi)
    }
}

void app_main() {
    tcpip_adapter_init();
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    start_ap();
}