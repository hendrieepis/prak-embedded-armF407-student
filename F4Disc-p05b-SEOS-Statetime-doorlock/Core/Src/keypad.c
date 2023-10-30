/*
 * keypad.c
 *
 *  Created on: Aug 26, 2023
 *      Author: hendri
 */
#include "keypad.h"
#include "main.h"
#include "stdio.h"

unsigned char Button1_OK(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(BTN_UP_GPIO_Port,BTN_UP_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		printf("1-OK \n\r");
		//		print_UART2("1-OK",5);
		detectedFLag=1;
	}
	return detectedFLag;
}

unsigned char Button2_OK(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		printf("2-OK \n\r");
		//		print_UART2("2-OK",5);
		detectedFLag=1;
	}
	return detectedFLag;
}

unsigned char Button3_OK(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port,BTN_RIGHT_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		printf("3-OK \n\r");
		//		print_UART2("3-OK",5);
		detectedFLag=1;
	}
	return detectedFLag;
}

unsigned char Button4_OK(void){
	static unsigned char debounce=0xFF;
	unsigned char detectedFLag=0;
	if(HAL_GPIO_ReadPin(BTN_DN_GPIO_Port,BTN_DN_Pin)== GPIO_PIN_RESET){
		debounce=(debounce<<1);
	} else {
		debounce= (debounce<<1)|1;
	}
	if (debounce==0x03) {
		printf("4-OK \n\r");
		//		print_UART2("4-OK",5);
		detectedFLag=1;
	}
	return detectedFLag;
}
