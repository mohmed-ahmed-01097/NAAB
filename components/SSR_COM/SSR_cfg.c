/*
 * SSR_cfg.c
 *
 *  Created on: Sep 11, 2024
 *      Author: MAAM
 */

#include "SSR_cfg.h"
#include "driver/gpio.h"
#include <stdint.h>

gpio_num_t SSR_Ch[SSR_Channel_Max_Num] = {
	 GPIO_NUM_32
#if (SSR_Channel_Max_Num >= 2)
	,GPIO_NUM_33
 #if (SSR_Channel_Max_Num >= 3)
	,GPIO_NUM_23
  #if (SSR_Channel_Max_Num >= 4)
	,GPIO_NUM_2
  #endif
 #endif
#endif
};

