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
    hSCH_init(1);
    hSCH_Add_Task(task1_update, 0, 1000,0);
    hSCH_Add_Task(task2_update, 100, 1000,0);
    hSCH_Add_Task(task3_update, 200, 1000,1);
    /* Start the scheduler */
    hSCH_Start();
    while (1)
    {
        hSCH_Dispatch_Tasks();
    }
	return 0;
}




