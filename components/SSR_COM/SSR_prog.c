/*
 * SSR_prog.c
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */

#include "SSR_init.h"
#include "esp_log.h"

extern gpio_num_t SSR_Ch[SSR_Channel_Max_Num];

void SSR_Init(void){
	for(uint8_t i = 0 ; i<SSR_Channel_Num ; i++){
		gpio_set_direction(SSR_Ch[i], GPIO_MODE_OUTPUT);
    	gpio_set_level    (SSR_Ch[i],SSR_lEVEL_OFF   );
    	ESP_LOGI(TAG, "Channel %u Configured successfully", i);
	}
}

void SSR_SetLevel(uint8_t u8Channel, uint8_t u8Level){
	u8Level ^= SSR_lEVEL_OFF;
    gpio_set_level(SSR_Ch[u8Channel],u8Level);
    ESP_LOGI(TAG, "Relay %u Turned %s", u8Channel, (u8Level ? "ON" : "OFF"));
}

