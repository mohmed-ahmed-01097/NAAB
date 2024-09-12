idf_component_register(SRCS "RTDB_prog.cpp"
                    INCLUDE_DIRS "." ".."
                    REQUIRES SSR_COM json nvs_flash esp_event esp_wifi
                    PRIV_REQUIRES esp_http_client)
