/*
 * RTDB_prog.cpp
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */

#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "jsoncpp/value.h"
#include "jsoncpp/json.h"

#include "esp_firebase/app.h"
#include "esp_firebase/rtdb.h"
#include "cJSON.h"

#include "SSR_COM/SSR_cfg.h"
#include "SSR_COM/SSR_init.h"
#include "ESP_COM/ESP_init.h"
#include "RTDB_cfg.h"

#define TAG				"RTDB"

using namespace ESPFirebase;
// Declare db as a pointer
ESPFirebase::RTDB* db = nullptr;
// Construct a new json object manually
Json::Value new_data; 

extern "C" void RTDB_Init(void *pvParameters)
{
    (void) pvParameters;  // Prevent unused parameter warning
	
	SSR_Init();
	
    // Config and Authentication
    user_account_t account = {USER_EMAIL, USER_PASSWORD};

    FirebaseApp app = FirebaseApp(API_KEY);

    app.loginUserAccount(account);

    db = new RTDB(&app, DATABASE_URL);

    // vTaskDelay(500/portTICK_PERIOD_MS);
	new_data[RTDB_SSR_CH0] = SSR_lEVEL_OFF;
#if (SSR_Channel_Max_Num >= 2)
	new_data[RTDB_SSR_CH1] = SSR_lEVEL_OFF;
 #if (SSR_Channel_Max_Num >= 3)
	new_data[RTDB_SSR_CH2] = SSR_lEVEL_OFF;
  #if (SSR_Channel_Max_Num >= 4)
	new_data[RTDB_SSR_CH3] = SSR_lEVEL_OFF;
  #endif
 #endif
#endif

    db->putData(RTDB_PATH, new_data);
    // vTaskDelay(500/portTICK_PERIOD_MS);

    

    Json::FastWriter writer;
    std::string person3_string_prev = "";
    while (1)
    {
        
        Json::Value root = db->getData(RTDB_PATH); // retrieve person3 from database, set it to "" to get entire database
        std::string person3_string = writer.write(root);  // convert it to json string
        if(strcmp(person3_string_prev.c_str(), person3_string.c_str())){
                
            ESP_LOGI(TAG, "%s as json string: \n%s", RTDB_PATH, person3_string.c_str());

            cJSON *root1 = cJSON_Parse(person3_string.c_str());

            if (root1 != NULL)
            {
            	cJSON *appliance1 = cJSON_GetObjectItem(root1, RTDB_SSR_CH0);
#if (SSR_Channel_Max_Num >= 2)
            	cJSON *appliance2 = cJSON_GetObjectItem(root1, RTDB_SSR_CH1);
 #if (SSR_Channel_Max_Num >= 3)
            	cJSON *appliance3 = cJSON_GetObjectItem(root1, RTDB_SSR_CH2);
  #if (SSR_Channel_Max_Num >= 4)
            	cJSON *appliance4 = cJSON_GetObjectItem(root1, RTDB_SSR_CH3);
  #endif
 #endif
#endif

            	if (appliance1 && appliance1->type == cJSON_Number){
                	SSR_SetLevel(0, appliance1->valueint);
            	}
#if (SSR_Channel_Max_Num >= 2)
            	if (appliance2 && appliance2->type == cJSON_Number){
                	SSR_SetLevel(1, appliance2->valueint);
            	}
 #if (SSR_Channel_Max_Num >= 3)
            	if (appliance3 && appliance3->type == cJSON_Number){
                	SSR_SetLevel(2, appliance3->valueint);
            	}
  #if (SSR_Channel_Max_Num >= 4)
            	if (appliance4 && appliance4->type == cJSON_Number){
                	SSR_SetLevel(3, appliance4->valueint);
            	}
  #endif
 #endif
#endif

            }
            // You can also print entire Json Value object with std::cout with converting to string 
            // you cant print directly with printf or LOGx because Value objects can have many type. << is overloaded and can print regardless of the type of the Value
            std::cout << root << std::endl;

            // print the members (Value::Members is a vector)
            Json::Value::Members members = root.getMemberNames();  
            for (const auto& member : members)
            {
                std::cout << member << ", ";
            }
            std::cout << std::endl;
            person3_string_prev = person3_string;
            vTaskDelay(100);
        }
        vTaskDelay(200);
    }
}


