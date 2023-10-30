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

// *** edit only in this line below **
#define SCH_MAX_TASKS 4
/* Type definition here ------------------------------------ */
#define RETURN_NORMAL  0
#define RETURN_ERROR  1
//************************************



// Error codes
//----------------------------------------------------------------------
#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)

// --Global function here ------------------

typedef struct
{
  void (* pTask)(void);
  uint16_t Delay;
  uint16_t Period;
  uint8_t RunMe;
} sTask;

uint8_t Error_code_G;
sTask SCH_tasks_G[SCH_MAX_TASKS];


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if((htim->Instance)==TIM2){
//		HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin); //debuging LED
		SCH_update();
	}
}


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
}


uint8_t SCH_Add_Task(void (* pFunction)(),uint16_t DELAY,uint16_t PERIOD)
{
	uint8_t Index = 0;
	/* First find a gap in the array (if there is one) */
	while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
		Index++;
	}
	/* Have we reached the end of the list? */
	if (Index == SCH_MAX_TASKS){
		/* Task list is full
    -> set the global error variable */
		Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
		/* Also return an error code */
		return SCH_MAX_TASKS;
	}
	/* If we're here, there is a space in the task array */
	SCH_tasks_G[Index].pTask = pFunction;
	SCH_tasks_G[Index].Delay = DELAY + 1;
	SCH_tasks_G[Index].Period = PERIOD;
	SCH_tasks_G[Index].RunMe = 0;
	return Index; /* return pos. of task (to allow deletion) */
}


void SCH_Dispatch_Tasks(void)
{
	uint8_t Index;
	/* Dispatches (runs) the next task (if one is ready) */
	for (Index = 0; Index < SCH_MAX_TASKS; Index++){
		if (SCH_tasks_G[Index].RunMe > 0){
			(*SCH_tasks_G[Index].pTask)(); /* Run the task */
			SCH_tasks_G[Index].RunMe --; /* Reduce RunMe count */
			/* Periodic tasks will automatically run again
      - if this is a 'one shot' task, delete it */
			if (SCH_tasks_G[Index].Period == 0){
				SCH_Delete_Task(Index);
			}
		}
	}
	/* Report system status */
	//SCH_Report_Status();
	/* The scheduler enters idle mode at this point */
//	sleep_mode();
}


uint8_t SCH_Delete_Task(const uint8_t TASK_INDEX)
{
	unsigned char Return_code;
	if (SCH_tasks_G[TASK_INDEX].pTask == 0){
		/* No task at this location...
    -> set the global error variable */
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		/* ...also return an error code */
		Return_code = RETURN_ERROR;
	}
	else {
		Return_code = RETURN_NORMAL;
	}
	SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
	SCH_tasks_G[TASK_INDEX].Delay = 0;
	SCH_tasks_G[TASK_INDEX].Period = 0;
	SCH_tasks_G[TASK_INDEX].RunMe = 0;
	return Return_code; /* return status */
}

void SCH_update(void)
{
	uint8_t Index;
	/* NOTE: calculations are in *TICKS* (not milliseconds) */
	for (Index = 0; Index < SCH_MAX_TASKS; Index++){
		/* Check if there is a task at this location */
		if (SCH_tasks_G[Index].pTask){
			if (--SCH_tasks_G[Index].Delay == 0){
				/* The task is due to run */
				SCH_tasks_G[Index].RunMe++; /* Inc. 'RunMe' flag */
				if (SCH_tasks_G[Index].Period){
					/* Schedule regular tasks to run again */
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			}
		}
	}
}


/*--------------------------------------------------------*/
void SCH_Report_Status(void)
{
#ifdef SCH_REPORT_ERRORS
	/* ONLY APPLIES IF WE ARE REPORTING ERRORS */
	/* Check for a new error code */
	if (Error_code_G != Last_error_code_G)
	{
		/* Negative logic on LEDs assumed */
		Error_port = 255 - Error_code_G;
		Last_error_code_G = Error_code_G;
		if (Error_code_G != 0)
		{
			Error_tick_count_G = 60000;
		}
		else
		{
			Error_tick_count_G = 0;
		}
	}
	else
	{
		if (Error_tick_count_G != 0)
		{
			if (--Error_tick_count_G == 0)
			{
				Error_code_G = 0; /* Reset error code */
			}
		}
	}
#endif
}
