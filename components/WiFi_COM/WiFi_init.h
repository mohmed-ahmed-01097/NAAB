/*
 * WiFi_init.h
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */

#ifndef MAIN_WIFI_COM_WIFI_INIT_H_
#define MAIN_WIFI_COM_WIFI_INIT_H_


#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include <string.h>
#include "lwip/err.h"
#include "lwip/sys.h"

#include "esp_wifi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void WiFi_Init(void);


#ifdef __cplusplus
}
#endif

#endif /* MAIN_WIFI_COM_WIFI_INIT_H_ */
