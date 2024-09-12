/*
 * WiFi_cfg.h
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */

#ifndef MAIN_WIFI_COM_WIFI_CFG_H_
#define MAIN_WIFI_COM_WIFI_CFG_H_

#define TAG		 						"WiFi"

#define WIFI_SSID						"M.A.A.M" 				//"MAAM phone"				// input your home or public wifi name 
#define WIFI_PASS						"01001280981Newmgh"		//"12345678"				// password of wifi ssid

#define MAX_CONN						2u
#define CHANNEL							6u

#define WIFI_SCAN_RUNNING				(-1)
#define WIFI_SCAN_FAILED				(-2)

#define EXAMPLE_ESP_MAXIMUM_RETRY		5u

#define WIFI_CONNECTED_BIT				BIT0
#define WIFI_FAIL_BIT					BIT1


#endif /* MAIN_WIFI_COM_WIFI_CFG_H_ */
