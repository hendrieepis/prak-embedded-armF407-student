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

void Task_Init(void){
  HAL_Delay(1);  //fix bug not display
  printf("Task init ..... Started \n\r");

}

void Task_Run(void){
//	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin); //debuging LED
	if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port,BTN_LEFT_Pin)== GPIO_PIN_RESET){
		bouncing=(bouncing<<1);
	} else {
		bouncing= (bouncing<<1)|1;
	}
	if (bouncing==0x03) {
		CounterUpdate();
		printf ("count:%d \n\r",CounterGetValue());
	}
	counterShow();
}

