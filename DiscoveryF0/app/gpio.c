/*
 * gpio.c
 *
 *  Created on: Aug 23, 2025
 *      Author: aleksey
 */


#include "gpio.h"
extern uint8_t blinked;
extern GPIO_TypeDef * LED_GPIO_Port;
uint16_t LED_Pin = GreenLED_Pin;
uint32_t myTick = 0;

void init_led(GPIO_TypeDef* port, uint16_t pin)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();
	HAL_GPIO_WritePin(GPIOC, BlueLED_Pin|GreenLED_Pin, GPIO_PIN_RESET);
	  /*Configure GPIO pin : LED_Pin */
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	  GPIO_InitStruct.Pin = pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == Button_Pin)
		blinked = ! blinked;
}

void loop()
{
	  if (blinked)
		  {	if ((HAL_GetTick() - myTick) < DARKTIME)
				  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LedOff);
			else if (((HAL_GetTick() - myTick) >= DARKTIME) && ((HAL_GetTick() - myTick) < (DARKTIME + FLASHTIME)))
				  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LedOn);
			else if ((HAL_GetTick() - myTick) >= (DARKTIME + FLASHTIME))
			  {
				  myTick = HAL_GetTick();
				  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LedOff);
				  if (LED_Pin == GreenLED_Pin)
					  LED_Pin = BlueLED_Pin;
				  else
					  LED_Pin = GreenLED_Pin;
			  }
		  }
	  else
		  {
			  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, LedOff);
			  myTick = HAL_GetTick();
		  }
}
