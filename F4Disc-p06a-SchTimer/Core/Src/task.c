/*
 * task.c
 *
 *  Created on: Aug 26, 2023
 *      Author: hendri
 */
#include "task.h"
#include "task.h"
#include "main.h"
#include "stdio.h"


void task1_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin);
}

void task2_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(LD4_GPIO_Port,LD4_Pin);
}


void task3_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(LD5_GPIO_Port,LD5_Pin);
}


void task4_update(void)
{
	//dummy running task
	HAL_GPIO_TogglePin(LD6_GPIO_Port,LD5_Pin);
}


