/*
 * main.cpp
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ESP_COM/ESP_init.h"
#include "RTDB_COM/RTDB_init.h"
#include "WiFi_COM/WiFi_init.h"
#include "SSR_COM/SSR_init.h"

void app_main(void)
{
	ESP_ChipInfo();
	WiFi_Init();
	RTDB_Init();
	
    while (true) {
        printf(">>>>>>>>>>>>>>>>>>>>>>> Ideal While Loop \n");
        sleep(1);
    }
}


