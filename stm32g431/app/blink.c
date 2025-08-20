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
	  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, a);
	  HAL_Delay(500);
	  a = !a;
}
