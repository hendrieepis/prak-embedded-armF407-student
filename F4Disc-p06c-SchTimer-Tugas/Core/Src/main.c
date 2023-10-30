// task1 object counting
// task2 blinky setiap 400ms
// task3 kirim informasi ke uart setiap 2 dtk sekali kata "hello"

#include "main.h"
#include "usb_device.h"
#include "hardwareinit.h"
#include "seos.h"
#include "checkboard.h"
#include "counter.h"
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
	/* Prepare for the 'Flash_LED' task */
	//	  TaskInit();
	/* Set up the scheduler */
	SCH_Add_Task(task1_update, 0, 2);   //object counting
	SCH_Add_Task(task2_update, 0, 400); //blinky setiap 400ms
	SCH_Add_Task(task3_update, 0, 2000); // send hello to serial each 2s
	//	SCH_Add_Task(task4_update, delay+0, periode);
	SCH_START();
	while (1)
	{
		SCH_Dispatch_Tasks();
	}
}




