/*
 * 7seg.c
 *
 *  Created on: Aug 23, 2025
 *      Author: aleksey
 */

#include <seg7.h>
uint8_t digit = 0;
extern uint32_t myTick;
//7seg знакогенератор 
uint16_t digits[10] = {
                    (A_Pin|B_Pin|C_Pin|D_Pin|E_Pin|F_Pin), 			// "0"
					(B_Pin|C_Pin), 									// "1"
					(A_Pin|B_Pin|D_Pin|E_Pin|G_Pin), 				// "2"
					(A_Pin|B_Pin|C_Pin|D_Pin|G_Pin), 				// "3"
					(B_Pin|C_Pin|F_Pin|G_Pin), 						// "4"
					(A_Pin|C_Pin|D_Pin|F_Pin|G_Pin), 				// "5"
					(A_Pin|C_Pin|D_Pin|E_Pin|F_Pin|G_Pin), 			// "6"
					(A_Pin|B_Pin|C_Pin), 							// "7"
					(A_Pin|B_Pin|C_Pin|D_Pin|E_Pin|F_Pin|G_Pin),	// "8"
					(A_Pin|B_Pin|C_Pin|D_Pin|F_Pin|G_Pin), 			// "9"
                  };

//  функция display_symbol - отображает цифру symbol в разряде decimal_place
void display_symbol(int symbol, int decimal_place) 
{
	if (decimal_place == 1)
	{
		HAL_GPIO_WritePin(DispPort, _D1_Pin, GPIO_PIN_SET);
	} else if (decimal_place == 2)
	{
		HAL_GPIO_WritePin(DispPort, _D2_Pin, GPIO_PIN_SET);
	} else if (decimal_place == 3)
	{
		HAL_GPIO_WritePin(DispPort, _D3_Pin, GPIO_PIN_SET);
	}
	HAL_GPIO_WritePin(DispPort, digits[symbol], GPIO_PIN_SET);
}

// функция dark_all() - гасит все сегменты индикатора
void dark_all()
{
	HAL_GPIO_WritePin(DispPort, _D1_Pin|_D2_Pin|_D3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DispPort, digits[8], GPIO_PIN_RESET);
}

//  функция display - отображает число value 
void display(int value)
{
	  uint8_t digit[3] = {0};
	  static int current_digit = 1;
	  for (int i = 2; i > 0; i--)
		  {
			digit[i] = value % 10;
			value = value / 10;
		  }
		if(HAL_GetTick() - myTick < LIGHTTIME)
		{
			display_symbol(digit[current_digit - 1], current_digit);

		} else {
			myTick = HAL_GetTick();
			(current_digit==3) ? current_digit = 0 : current_digit++;
			dark_all();
		}

}


