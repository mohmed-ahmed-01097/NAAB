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

#include "RTDB_cfg.h"
#include "ESP_COM/ESP_init.h"
#include "SSR_COM/SSR_init.h"

using namespace ESPFirebase;
extern "C" void RTDB_Init(void)
{
	
	SSR_Init();
	
    // Config and Authentication
    user_account_t account = {USER_EMAIL, USER_PASSWORD};

    FirebaseApp app = FirebaseApp(API_KEY);

    app.loginUserAccount(account);

    RTDB db = RTDB(&app, DATABASE_URL);



    // vTaskDelay(500/portTICK_PERIOD_MS);
    // Construct a new json object manually
    Json::Value new_data; 
    new_data["Appliances1"] = 0;
    new_data["Appliances2"] = 0;
    new_data["Appliances3"] = 0;
    new_data["Appliances4"] = 0;

    db.putData("Bedroom", new_data);
    // vTaskDelay(500/portTICK_PERIOD_MS);

    

    Json::FastWriter writer;
    std::string person3_string_prev = "";
    while (1)
    {
        
        Json::Value root = db.getData("Bedroom"); // retrieve person3 from database, set it to "" to get entire database
        std::string person3_string = writer.write(root);  // convert it to json string
        if(strcmp(person3_string_prev.c_str(), person3_string.c_str())){
                
            ESP_LOGI("MAIN", "Bedroom as json string: \n%s", person3_string.c_str());

            cJSON *root1 = cJSON_Parse(person3_string.c_str());

            if (root1 != NULL)
            {
                cJSON *appliance1 = cJSON_GetObjectItem(root1, "Appliances1");
                cJSON *appliance2 = cJSON_GetObjectItem(root1, "Appliances2");
                cJSON *appliance3 = cJSON_GetObjectItem(root1, "Appliances3");
                cJSON *appliance4 = cJSON_GetObjectItem(root1, "Appliances4");

                if (appliance1 && appliance1->type == cJSON_Number){
                    SSR_SetLevel(0, appliance1->valueint);
                }

                if (appliance2 && appliance2->type == cJSON_Number){
                    SSR_SetLevel(1, appliance2->valueint);
                }

                if (appliance3 && appliance3->type == cJSON_Number){
                    SSR_SetLevel(2, appliance3->valueint);
                }

                if (appliance4 && appliance4->type == cJSON_Number){
                    SSR_SetLevel(3, appliance4->valueint);
                }

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
    }
}





