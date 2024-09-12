idf_component_register(SRCS "ESP_prog.c"
                    INCLUDE_DIRS "." ".."
    				REQUIRES nvs_flash esp_event esp_wifi)
