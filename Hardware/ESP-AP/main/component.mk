#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

 COMPONENT_SRCDIRS += wifi_ap wifi_sta httpd_server mqttd_client board_led commad_handler
 COMPONENT_ADD_INCLUDEDIRS += wifi_ap wifi_sta httpd_server mqttd_client board_led commad_handler
