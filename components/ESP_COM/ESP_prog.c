/*
 * ESP_prog.c
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */

#include "ESP_init.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_mac.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

void ChipID(void) {
	uint8_t mac_addr[6];
    
    // Get the MAC address of the chip
    esp_efuse_mac_get_default(mac_addr);
    
    // Get and print the chip ID
    static char str[13] ;
    snprintf(str, 13, "%02x%02x%02x%02x%02x%02x", mac_addr[5],mac_addr[4],mac_addr[3],mac_addr[2],mac_addr[1],mac_addr[0]); 
    
    // Initialize logging
    esp_log_level_set("*", ESP_LOG_INFO);

    ESP_LOGI("CHIP_ID", "Chip ID: MAAM_SP1_%s", str);
}

void ESP_ChipInfo(void){
	
    /* Print chip information */
    esp_chip_info_t chip_info;
    uint32_t flash_size;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), %s%s%s%s, silicon revision v%d.%d",
           CONFIG_IDF_TARGET,
           chip_info.cores,
           (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "WiFi/" : "",
           (chip_info.features & CHIP_FEATURE_BT) ? "BT/" : "",
           (chip_info.features & CHIP_FEATURE_BLE) ? "BLE/" : "",
           (chip_info.features & CHIP_FEATURE_IEEE802154) ? ", 802.15.4 (Zigbee/Thread)" : "",
           (chip_info.revision / 100),
           (chip_info.revision % 100));

    if(esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
        printf("Get flash size failed");
        return;
    }

    printf("%" PRIu32 "MB %s flash\n", flash_size / (uint32_t)(1024 * 1024),
           (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %" PRIu32 " bytes\n", esp_get_minimum_free_heap_size());

}

