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
#include "SPIFFS_COM/SPIFFS_init.h"

#define STACK_SIZE		1024
#define TAG				"main"

// Correct task function prototype with FreeRTOS signature
void Idle_Task(void *pvParameters);

// Stack overflow hook function (optional for debugging)
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    // This function will be called if a stack overflow is detected
    printf("Stack overflow in task: %s\n", pcTaskName);
    abort();  // Halt the program
}

void app_main(void)
{
	BaseType_t result;
	ESP_ChipInfo();
	ChipID();
	spiffs_test();
	
    // Create the task and pin it to core 1 (core 0 might be reserved for system tasks)
    result = xTaskCreatePinnedToCore(
        Idle_Task,			// Task function
        "IDLE",					// Task name
        STACK_SIZE,		// Stack size
        NULL,				// Task input parameter (none in this case)
        tskIDLE_PRIORITY,	// Task priority
        NULL,				// Task handle (not used)
        1						// Core ID (0 or 1; use 1 for user tasks to avoid conflicts)
    );

    // Check if the task was created successfully
    if (result != pdPASS) {
        printf("Task creation failed!\n");
    }
      
	WiFi_Init();
	//RTDB_Init();
	
    // Create the task and pin it to core 1 (core 0 might be reserved for system tasks)
    result = xTaskCreatePinnedToCore(
        RTDB_Init,			// Task function
        "RTDB",					// Task name
        0x40*STACK_SIZE,		// Stack size
        NULL,				// Task input parameter (none in this case)
        1,					// Task priority
        NULL,				// Task handle (not used)
        1						// Core ID (0 or 1; use 1 for user tasks to avoid conflicts)
    );
    // Check if the task was created successfully
    if (result != pdPASS) {
        printf("Task creation failed!\n");
    }
    // Configure light sleep
    //esp_sleep_enable_timer_wakeup(SLEEP_DURATION_MS * 1000); // Wakeup after 100 milliseconds

    while (true) {
        printf(">>>>>>>>>>>>>>>>>>>>>>> main While Loop >>>>>>>>>>>>>>>>>>>>>>>\n");
        sleep(1);
        //vTaskDelay(1000);
        //ESP_LOGI(TAG, "Entering light sleep");
        //esp_light_sleep_start();  // Enter light sleep mode
        //vTaskDelay(SLEEP_DURATION_MS);
        //ESP_LOGI(TAG, "Waking up from light sleep");
    }
}

// Correct task function definition
void Idle_Task(void *pvParameters) {
    (void) pvParameters;  // Prevent unused parameter warning

    // Task loop
    while (true) {
        printf(">>>>>>>>>>>>>>>>>>>>>>> Idle While Loop \n");
        vTaskDelay(1000);
        //sleep(1);  // Sleep for 1 second
        // Delay for 500 milliseconds
        //vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

