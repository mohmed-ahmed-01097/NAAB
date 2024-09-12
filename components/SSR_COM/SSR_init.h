/*
 * SSR_init.h
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */

#ifndef MAIN_SSR_COM_SSR_INIT_H_
#define MAIN_SSR_COM_SSR_INIT_H_

#include <stdint.h>
#include "driver/gpio.h"
#include "SSR_COM/SSR_cfg.h"

typedef enum{
	 SSR_Channel_0 = 0
#if (SSR_Channel_Max_Num >= 2)
	,SSR_Channel_1
 #if (SSR_Channel_Max_Num >= 3)
	,SSR_Channel_2
  #if (SSR_Channel_Max_Num >= 4)
	,SSR_Channel_3
  #endif
 #endif
#endif
	,SSR_Channel_Num
}SSR_tenuChannel;

#ifdef __cplusplus
extern "C" {
#endif

void SSR_Init(void);
void SSR_SetLevel(uint8_t u8Channel, uint8_t u8Level);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_SSR_COM_SSR_INIT_H_ */
