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

//Private constant-----------------------
#define LAMA_MERAH	5
#define LAMA_KUNING	2
#define LAMA_HIJAU	4

#define MerahON   HAL_GPIO_WritePin(BAR2_GPIO_Port,BAR2_Pin,GPIO_PIN_SET)
#define MerahOFF  HAL_GPIO_WritePin(BAR2_GPIO_Port,BAR2_Pin,GPIO_PIN_RESET)

#define KuningON  HAL_GPIO_WritePin(BAR3_GPIO_Port,BAR3_Pin,GPIO_PIN_SET)
#define KuningOFF HAL_GPIO_WritePin(BAR3_GPIO_Port,BAR3_Pin,GPIO_PIN_RESET)

#define HijauON	   HAL_GPIO_WritePin(BAR4_GPIO_Port,BAR4_Pin,GPIO_PIN_SET)
#define HijauOFF   HAL_GPIO_WritePin(BAR4_GPIO_Port,BAR4_Pin,GPIO_PIN_RESET)

//Private variable-----------------------
enum state {merah, kuning, hijau } stateku;
unsigned int Time_in_state=0;

/* -------------------------------------- *
	Traffic_Light_Init()
	Set kondisi pertama ke merah
-* -------------------------------------- */

void Task_Init(void){
  HAL_Delay(1);  //fix bug not display
  printf("Task init ..... Started \n\r");
  stateku=merah;

}

void Task_Run(void){

	//	USARTPutStr("."); //current state
		switch(stateku)
		{
			case merah:
		        {

					MerahON;
					KuningOFF;
					HijauOFF;
					printf("Merah ON %d: \n\r",Time_in_state+1);
		        	if (++Time_in_state==LAMA_MERAH)
		        	{
		        		stateku=kuning;
		        		Time_in_state=0;
		        	}

		        	break;
		        }

			case kuning:
		        {

		        	MerahOFF;
		        	KuningON;
		        	HijauOFF;
		        	printf("Kuning ON %d: \n\r",Time_in_state+1);
		        	if (++Time_in_state==LAMA_KUNING)
		        	{
		        		stateku=hijau;
		        		Time_in_state=0;
		        	}

		        	break;
		        }

			case hijau:
		        {
	                MerahOFF;
	                KuningOFF;
	                HijauON;
	                printf("Hijau ON %d: \n\r", Time_in_state+1);
		        	if (++Time_in_state==LAMA_HIJAU)
		        	{
		        		stateku=merah;
		        		Time_in_state=0;
		        	}

		        	break;
		        }
		}

}


