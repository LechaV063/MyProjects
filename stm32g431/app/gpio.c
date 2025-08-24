/*
 * gpio.c
 *
 *  Created on: Aug 22, 2025
 *      Author: aleksey
 */

#include "seg7.h"
#include "gpio.h"
extern uint16_t digits[10];
extern uint16_t counter;
uint8_t LedOff = 1;
uint8_t LedOn = 0;

void init_led(GPIO_TypeDef* port, uint16_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	  /*Configure GPIO pins : A_Pin B_Pin C_Pin CB10_Pin
	                           _D3_Pin _D2_Pin _D1_Pin D_Pin
	                           E_Pin F_Pin G_Pin DPoint_Pin */
	  HAL_GPIO_WritePin(GPIOB, A_Pin|B_Pin|C_Pin|CB10_Pin
	                          |_D3_Pin|_D2_Pin|_D1_Pin|D_Pin
	                          |E_Pin|F_Pin|G_Pin|DPoint_Pin, GPIO_PIN_RESET);
	  GPIO_InitStruct.Pin = A_Pin|B_Pin|C_Pin|CB10_Pin
	                          |_D3_Pin|_D2_Pin|_D1_Pin|D_Pin
	                          |E_Pin|F_Pin|G_Pin|DPoint_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void init_Button(GPIO_TypeDef* port,uint16_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/*Configure GPIO pin : Button_Pin */
	GPIO_InitStruct.Pin = Button_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(port, &GPIO_InitStruct);
	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}


void setup()
{
	  init_led(GPIOB, A_Pin|B_Pin|C_Pin|CB10_Pin
	          |_D3_Pin|_D2_Pin|_D1_Pin|D_Pin
	          |E_Pin|F_Pin|G_Pin|DPoint_Pin);
	  init_Button(Button_GPIO_Port, Button_Pin);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == Button_Pin)
		counter++;
}

void loop()
{
	display(counter);
}
