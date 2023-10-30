/*
 * sensor.c
 *
 *  Created on: Aug 22, 2023
 *      Author: hendri
 */
#include "sensor.h"
#include "main.h"
// sensor.c dan sensor.h
uint8_t sensorDetected(void){
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}

uint8_t resetDetected(void){
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port,BTN_RIGHT_Pin)== GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port,BTN_RIGHT_Pin)== GPIO_PIN_RESET) {
			while(HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port,BTN_RIGHT_Pin)== GPIO_PIN_RESET);
			FlagDetect=1;
		}
	}
	return FlagDetect;
}
