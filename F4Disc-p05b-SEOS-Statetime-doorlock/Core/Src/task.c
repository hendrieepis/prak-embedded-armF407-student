/*
 * task.c
 *
 *  Created on: Aug 26, 2023
 *      Author: hendri
 */
#include "task.h"
#include "main.h"
#include "stdio.h"
#include "keypad.h"


//Private constant-----------------------
#define doorOpen   HAL_GPIO_WritePin(BAR2_GPIO_Port,BAR2_Pin,GPIO_PIN_SET)
#define doorClose  HAL_GPIO_WritePin(BAR2_GPIO_Port,BAR2_Pin,GPIO_PIN_RESET)
#define buzzerON   HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_SET)
#define buzzerOFF  HAL_GPIO_WritePin(BUZZER_GPIO_Port,BUZZER_Pin,GPIO_PIN_RESET)
#define YES 1
#define NO 0
//Private variable-----------------------
enum state {start,startDelay, enterpass, check, open,openDelay, alarm, resetalarm, resetverify} Kondisi;
volatile uint8_t label=0;
volatile uint8_t kombinasi[4]={0,0,0,0};
volatile uint8_t pressed=NO;
volatile uint8_t count=0;
volatile uint8_t fail_count=0;

volatile uint16_t timeout;

void Task_Init(void){
	timeout=0;
	Kondisi=start;
}

void Task_Run(void){

	switch(Kondisi)
	{
	case start:
	{
		printf("****     Alarm System   PENS 2023 ***** \n\r");
		Kondisi=startDelay;
		break;
	}
	case startDelay:
	{
		count=0;
		fail_count=0;
		HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_SET);
		if (++timeout > 1000) // dari scheduler sebesar 2ms*1000= 2 detik
		{
			printf("Enter Password  \n\r"); //current state
			HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_RESET);
			timeout=0;
			Kondisi=enterpass;
		}
		break;
	}
	case enterpass:
	{
		if(Button1_OK())
		{
			label=1;
			pressed=YES;
			timeout=0;
		}

		if (Button2_OK())
		{
			label=2;
			pressed=YES;
			timeout=0;
		}

		if (Button3_OK())
		{
			label=3;
			pressed=YES;
			timeout=0;
		}

		if (Button4_OK())
		{
			label=4;
			pressed=YES;
			timeout=0;
		}

		if (pressed==YES)
		{
			//geser karakter
//			kombinasi[0]=kombinasi[1]; kombinasi[1]=kombinasi[2]; kombinasi[2]=kombinasi[3];
//			kombinasi[3]=label;
			// atau pakai cara ini
			for (int i = 0; i < 3; i++) {
			    kombinasi[i] = kombinasi[i + 1];
			}
			kombinasi[3] = label;

			pressed=NO;
			label=0;
			count++;
			//			printf("*"); //current state
		}

		//sudah 4 karakter
		if (count>3) Kondisi=check;

		//jeda memasukkan password lebih dari 3 detik
		if ((++timeout>1500) && (count >0))
		{
			printf("Time Out!.......Access Denied! \n\r");
			Kondisi=alarm;
			timeout=0;
		}

		break;
	}
	case check:
	{
		if      ((kombinasi[0]==2)&&
				(kombinasi[1]==2)&&
				(kombinasi[2]==2)&&
				(kombinasi[3]==2))
		{
			Kondisi=open;
		}
		else
		{
			if (++fail_count >= 3)
			{
				Kondisi=alarm;
				printf("Fail 3x..... Access Denied! \n\r");
			}
			else
			{
				printf("Coba lagi \n\r");
				timeout=0;
				count=0;
				Kondisi=enterpass;
			}
		}

		break;
	}

	case open:
	{
		printf("Access Granted \n\r");
		doorOpen;
		Kondisi=openDelay;
		break;
	}
	case openDelay:
	{
		if (++timeout > 1000) // dari scheduler sebesar 2ms*1000= 2 detik
		{
			doorClose;
			buzzerOFF;
			Kondisi=start;
			timeout=0;
		}
		break;
	}

	case alarm:
	{
		buzzerON;
		count=0;
		pressed=NO;
		break;
	}

	case resetalarm:
	{
		//tugas
	}

	case resetverify:
	{
		//tugas
	}


	}

}



