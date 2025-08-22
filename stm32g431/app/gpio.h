/*
 * gpio.h
 *
 *  Created on: Aug 22, 2025
 *      Author: aleksey
 */

#ifndef GPIO_H_
#define GPIO_H_

#define DARKTIME 1000
#define FLASHTIME 50
#include "main.h"

void loop();
void init_led(GPIO_TypeDef* port,uint16_t pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* GPIO_H_ */
