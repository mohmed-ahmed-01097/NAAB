/*
 * RTDB_cfg.h
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */

#ifndef MAIN_RTDB_COM_RTDB_CFG_H_
#define MAIN_RTDB_COM_RTDB_CFG_H_


// The API key can be obtained from Firebase console > Project Overview > Project settings.
#define API_KEY					"AIzaSyDKFLaowKnwrgUmYlsAAtgbPbMpYU9ck0k"
#define DATABASE_URL			"https://bms-smart-grid-lab.firebaseio.com/"

// User Email and password that already registerd or added in your project.
#define USER_EMAIL				"BMS_esp32@maam.com"
#define USER_PASSWORD			"12345689"

#define RTDB_PATH				"MAAM_SP1_"

#define RTDB_SSR_CH0			"Channel_1"
#if (SSR_Channel_Max_Num >= 2)
#define RTDB_SSR_CH1			"Channel_2"
 #if (SSR_Channel_Max_Num >= 3)
#define RTDB_SSR_CH2			"Channel_3"
  #if (SSR_Channel_Max_Num >= 4)
#define RTDB_SSR_CH3			"Channel_4"
  #endif
 #endif
#endif


#endif /* MAIN_RTDB_COM_RTDB_CFG_H_ */
