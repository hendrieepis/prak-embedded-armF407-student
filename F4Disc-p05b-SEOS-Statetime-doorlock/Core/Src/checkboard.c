/*
 * checkboard.c
 *
 *  Created on: Aug 22, 2023
 *      Author: hendri
 */

#include "checkboard.h"
#include "main.h"
#include "stdio.h"
void checkBoard(void){
	  HAL_Delay(5000);
	  printf("Cek BarLED, buzzer, USER LED \n\r");
	  HAL_Delay(1000);
	  for (uint8_t cnt=0;cnt<8;cnt++){

		  HAL_GPIO_TogglePin(BAR0_GPIO_Port, BAR0_Pin);
		  HAL_GPIO_TogglePin(BAR1_GPIO_Port, BAR1_Pin);
		  HAL_GPIO_TogglePin(BAR2_GPIO_Port, BAR2_Pin);
		  HAL_GPIO_TogglePin(BAR3_GPIO_Port, BAR3_Pin);
		  HAL_GPIO_TogglePin(BAR4_GPIO_Port, BAR4_Pin);
		  HAL_GPIO_TogglePin(BAR5_GPIO_Port, BAR5_Pin);
		  HAL_GPIO_TogglePin(BAR6_GPIO_Port, BAR6_Pin);
		  HAL_GPIO_TogglePin(BAR7_GPIO_Port, BAR7_Pin);

		  HAL_GPIO_TogglePin(BUZZER_GPIO_Port, BUZZER_Pin);
		  HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
		  HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
		  HAL_GPIO_TogglePin(LD5_GPIO_Port, LD5_Pin);
		  HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
		  printf("count: %d \n\r",cnt);
		  HAL_Delay(100);
	  }

	  printf("Cek Button \n\r");
}

