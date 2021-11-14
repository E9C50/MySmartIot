set(COMPONENT_SRCS "main.c"
        "wifi_ap/wifi_ap.c" "wifi_sta/wifi_sta.c" "board_led/board_led.c"
        "httpd_server/httpd_server.c" "mqttd_client/mqttd_client.c"
        "command_handler/command_handler.c" "device_shadow/device_shadow.c")

register_component()
