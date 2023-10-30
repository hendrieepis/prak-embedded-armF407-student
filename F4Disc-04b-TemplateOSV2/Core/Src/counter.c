/*
 * counter.c
 *
 *  Created on: Aug 22, 2023
 *      Author: hendri
 */

#include "counter.h"
#include "stdint.h"
#include "main.h"
uint16_t count;

uint16_t counterShow(void){
	HAL_GPIO_WritePin(BAR0_GPIO_Port,BAR0_Pin,count & (1<<0));
	HAL_GPIO_WritePin(BAR1_GPIO_Port,BAR1_Pin,count & (1<<1));
	HAL_GPIO_WritePin(BAR2_GPIO_Port,BAR2_Pin,count & (1<<2));
	HAL_GPIO_WritePin(BAR3_GPIO_Port,BAR3_Pin,count & (1<<3));
	HAL_GPIO_WritePin(BAR4_GPIO_Port,BAR4_Pin,count & (1<<4));
	HAL_GPIO_WritePin(BAR5_GPIO_Port,BAR5_Pin,count & (1<<5));
	HAL_GPIO_WritePin(BAR6_GPIO_Port,BAR6_Pin,count & (1<<6));
	HAL_GPIO_WritePin(BAR7_GPIO_Port,BAR7_Pin,count & (1<<7));
	return count;
}
void CounterUpdate(void){
	++count;
}

void CounterZero(void){
	count=0;
}

uint8_t CounterGetValue(void){
	return (count);
}

