#include "main.h"
#include "usb_device.h"
#include "hardwareinit.h"
#include "seos.h"
#include "checkboard.h"
#include "task.h"

int main(void)
{

	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_I2S3_Init();
	MX_SPI1_Init();
	MX_USB_DEVICE_Init();
	checkBoard();
	SCH_INIT(1); //in ms
	uint16_t periode=1000;
	uint16_t delay=0;
	/* Prepare for the 'Flash_LED' task */
	//	  TaskInit();
	/* Set up the scheduler */
	SCH_Add_Task(task1_update, delay, periode);
	SCH_Add_Task(task2_update, delay+100, periode);
	SCH_Add_Task(task3_update, delay+200, periode);
	//	SCH_Add_Task(task4_update, delay+0, periode);
	SCH_START();
	while (1)
	{
		SCH_Dispatch_Tasks();
	}
}




