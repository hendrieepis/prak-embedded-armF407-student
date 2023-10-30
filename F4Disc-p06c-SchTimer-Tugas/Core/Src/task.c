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


void task1_update(void)
{
	if(sensorDetectedTimeout())
	{
//		printf("1-OK \n\r");
		CounterUpdate();
		printf ("count:%d \n\r",CounterGetValue());
	}

	if(resetDetectedTimeout())
	{
//		printf("1-OK \n\r");
		CounterZero();
		printf ("count:%d \n\r",CounterGetValue());
	}
}

void task2_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
}


void task3_update(void)
{
	//dummy running task
	printf("hello \n\r");
}


void task4_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(LD6_GPIO_Port,LD5_Pin);
}


