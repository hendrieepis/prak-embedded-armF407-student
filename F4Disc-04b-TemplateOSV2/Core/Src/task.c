/*
 * task.c
 *
 *  Created on: Aug 26, 2023
 *      Author: hendri
 */
#include "task.h"
#include "counter.h"
#include "task.h"
#include "main.h"
#include "stdio.h"
unsigned char bouncing=0xFF;
unsigned char sensorDetected(void);

void Task_Init(void){
  HAL_Delay(1);  //fix bug not display
  printf("Task init ..... Started \n\r");

}

void Task_Run(void){
	if(sensorDetected())
	{
//		printf("1-OK \n\r");
		CounterUpdate();
		printf ("count:%d \n\r",CounterGetValue());
	}
}


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
