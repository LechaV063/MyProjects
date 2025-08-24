/*
 * 7seg.h
 *
 *  Created on: Aug 23, 2025
 *      Author: aleksey
 */
#ifndef SEG7_H_
#define SEG7_H_

#include "main.h"

#define DispPort GPIOB
#define LIGHTTIME 2

void display_symbol(int symbol, int decimal_place); //
void display(int value);

#endif /* 7SEG_H_ */
