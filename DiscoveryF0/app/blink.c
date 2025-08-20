/*
 * blink.c
 *
 *  Created on: Aug 20, 2025
 *      Author: aleksey
 */


#include "blink.h"

void loop()
{
	HAL_GPIO_WritePin(GreenLED_GPIO_Port, GreenLED_Pin, 1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GreenLED_GPIO_Port, GreenLED_Pin, 0);
	HAL_Delay(2000);
	HAL_GPIO_WritePin(BlueLED_GPIO_Port, BlueLED_Pin, 1);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BlueLED_GPIO_Port, BlueLED_Pin, 0);
	HAL_Delay(2000);
}

void setup()
{}
