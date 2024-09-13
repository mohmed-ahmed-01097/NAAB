/*
 * SPIFFS_init.h
 *
 *  Created on: Sep 13, 2024
 *      Author: MAAM
 */

#ifndef COMPONENTS_SPIFFS_COM_SPIFFS_INIT_H_
#define COMPONENTS_SPIFFS_COM_SPIFFS_INIT_H_

#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t init_spiffs(void);
esp_err_t write_wifi_credentials(const char *ssid, const char *password);
esp_err_t read_wifi_credentials(char *ssid, size_t ssid_len, char *password, size_t password_len);
void spiffs_test(void);

#ifdef __cplusplus
}
#endif



#endif /* COMPONENTS_SPIFFS_COM_SPIFFS_INIT_H_ */
