/*
 task 1 blinky setiap 1 detik
 task 2 on 100ms off 5000ms
 task 3 object counting dengan timeout dan reset
 task 4 tombol userLED ditekan-> LED on 100ms off 3000ms
 *  Created on: Aug 26, 2023
 *      Author: hendri
 */

#include "task.h"
#include "counter.h"
#include "sensor.h"
#include "task.h"
#include "main.h"
#include "stdio.h"

#define LAMA_LED2ON	1
#define LAMA_LED2OFF	50

#define LED2ON   HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_SET)
#define LED2OFF  HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_RESET)
//Private variable-----------------------
enum state {s_on	, s_off} stateku=s_on;
unsigned int Time_in_state=0;
volatile uint32_t buttonPressTime = 0;

void task1_update(void)
{
  HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
}

void task2_update(void)
{
	switch(stateku)
	{
		case s_on:
	        {

				LED2ON;
//				printf("State  ON  >>>>>> ON %d: \n\r",Time_in_state+1);
	        	if (++Time_in_state==LAMA_LED2ON)
	        	{
	        		stateku=s_off;
	        		Time_in_state=0;
	        	}
	        	break;
	        }

		case s_off:
	        {
	        	LED2OFF;
//	        	printf("State OFF %d: \n\r",Time_in_state+1);
	        	if (++Time_in_state==LAMA_LED2OFF)
	        	{
	        		stateku=s_on;
	        		Time_in_state=0;
	        	}

	        	break;
	        }
	}
}


void task3_update(void)
{
	//dummy running task

	if(sensorDetectedTimeout())
	{
		CounterUpdate();
		printf ("count:%d \n\r",CounterGetValue());
	}

	if(resetDetectedTimeout())
	{
		CounterZero();
		printf ("count:%d \n\r",CounterGetValue());
	}
}


void task4_update(void)
{
	if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)) {
		 HAL_GPIO_WritePin(LD6_GPIO_Port,LD6_Pin,GPIO_PIN_SET);
		 buttonPressTime = HAL_GetTick();
	}

	if (HAL_GetTick()-buttonPressTime >=3000) {
		HAL_GPIO_WritePin(LD6_GPIO_Port,LD6_Pin,GPIO_PIN_RESET);
	}


}


