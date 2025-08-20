/*
 * blink.c
 *
 *  Created on: Aug 20, 2025
 *      Author: aleksey
 */


#include "blink.h"

 void setup()
 {}

 void loop()
{
	  static int a = 0;
	  HAL_GPIO_WritePin(Green_LED_GPIO_Port, Green_LED_Pin, a);
	  HAL_Delay(500);
	  a = !a;
}
