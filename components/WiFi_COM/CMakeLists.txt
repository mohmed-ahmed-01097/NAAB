idf_component_register(SRCS "WiFi_prog.c"
                    INCLUDE_DIRS "." ".."
    				REQUIRES driver nvs_flash esp_event esp_wifi)
