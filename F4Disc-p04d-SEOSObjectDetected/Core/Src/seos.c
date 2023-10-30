/*
 * seos.c
 *
 *  Created on: Aug 25, 2023
 *      Author: hendri
 */
#include "main.h"
#include "seos.h"
#include "task.h"

TIM_HandleTypeDef htim2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if((htim->Instance)==TIM2){
//		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin); //debuging LED
		Task_Run();
	}
}


/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
void MX_TIM2_Init(uint32_t periode)
{

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 42000-1; // harusnya 16 bit (0-65536)
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = (periode*2)-1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}


void SCH_INIT(uint32_t periode){
	/* Scheduler in ms */
	MX_TIM2_Init(periode);

	/* USER CODE END 2 */
}

void SCH_START(void){
	HAL_TIM_Base_Start_IT(&htim2);
	Task_Init();
}
