/*
 * ESP_init.h
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */

#ifndef MAIN_ESP_COM_ESP_INIT_H_
#define MAIN_ESP_COM_ESP_INIT_H_

#include "esp_chip_info.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_wifi.h"
#include "esp_flash.h"
#include "nvs_flash.h"

#ifdef __cplusplus
extern "C" {
#endif

void ESP_ChipInfo(void);
void ChipID(void);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_ESP_COM_ESP_INIT_H_ */
