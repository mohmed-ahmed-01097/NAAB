idf_component_register(SRCS "SPIFFS_prog.c"
                    INCLUDE_DIRS "." ".."
                    REQUIRES esp_event esp_wifi spiffs)
