/*
 * task.c
 *
 *  Created on: Aug 26, 2023
 *      Author: hendri
 */
#include "task.h"
#include "counter.h"
#include "sensor.h"
#include "task.h"
#include "main.h"
#include "stdio.h"


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


