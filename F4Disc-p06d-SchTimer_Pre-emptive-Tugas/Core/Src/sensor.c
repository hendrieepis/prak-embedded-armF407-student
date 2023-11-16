/*
 * sensor.c
 *
 *  Created on: Aug 26, 2023
 *      Author: hendri
 */
#include "main.h"
#include "sensor.h"
#include "stdio.h"

unsigned char sensorDetected(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		detectedFLag=1;
	}
	return detectedFLag;
}

uint8_t sensorDetectedTimeout(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;

	static uint32_t  Timeout_loop=0;
	uint32_t  Timeout_value=2000;

	if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET){
		if ((Timeout_loop++<=Timeout_value))
			debounce=(debounce<<1);
		else {
			printf("Err:001-btn cnt error  \n\r");
			if ((Timeout_value%200)==0) {
				HAL_GPIO_TogglePin(BUZZER_GPIO_Port,BUZZER_Pin);
			}
		}

	} else {
		debounce= (debounce<<1)|1;
		Timeout_loop=0;

	}
	if (debounce==0x03) {
		detectedFLag=1;
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}
	return detectedFLag;
}

unsigned char resetDetected(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port,BTN_RIGHT_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		detectedFLag=1;
	}
	return detectedFLag;
}


uint8_t resetDetectedTimeout(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;

	static uint32_t  Timeout_loop=0;
	uint32_t  Timeout_value=2000;

	if(HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port,BTN_RIGHT_Pin)== GPIO_PIN_RESET){
		if ((Timeout_loop++<=Timeout_value))
			debounce=(debounce<<1);
		else {
			printf("Err:002-btn reset error  \n\r");
			if ((Timeout_value%50)==0) {
				HAL_GPIO_TogglePin(BUZZER_GPIO_Port,BUZZER_Pin);
			}
		}

	} else {
		debounce= (debounce<<1)|1;
		Timeout_loop=0;
//		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}
	if (debounce==0x03) {
		detectedFLag=1;
		HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET);
	}
	return detectedFLag;
}

