/*
 * sensor.c
 *
 *  Created on: Aug 22, 2023
 *      Author: hendri
 */
#include "sensor.h"
#include "main.h"
#include "stdio.h"
// sensor.c dan sensor.h
//uint8_t sensorDetected(void){
//	uint8_t FlagDetect=0;
//	if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET) {
//		HAL_Delay(20);
//		if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET) {
//			while(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET);
//			FlagDetect=1;
//		}
//	}
//	return FlagDetect;
//}

uint8_t sensorDetected(void){
	uint32_t  Timeout_loop=0;
	uint32_t  Timeout_value=0x7FFFFF;
	uint8_t FlagDetect=0;
	if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)==GPIO_PIN_RESET) {
		HAL_Delay(20);
		if(!HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)) {
			while((!HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin))&& (Timeout_loop++<=Timeout_value));
			if (Timeout_loop>=Timeout_value)
			{
				HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_SET);
				HAL_Delay(1000);
				HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
				HAL_Delay(1000);
				printf("Err:001-btn error \n\r");
			} else
			{
				//				  CLR(buzzer);
				FlagDetect=1;
			}
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
