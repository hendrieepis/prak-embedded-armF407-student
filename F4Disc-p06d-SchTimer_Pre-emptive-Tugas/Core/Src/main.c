// task1 object counting
// task2 blinky setiap 400ms
// task3 kirim informasi ke uart setiap 2 dtk sekali kata "hello"

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
    hSCH_Add_Task(task1_update, 0, 1000,0);   //object counting
    hSCH_Add_Task(task2_update, 0, 100,0); //task 2 on 100ms off 5000ms
    hSCH_Add_Task(task3_update, 0, 2,0); // Task 3 object counting dengan reset dan timeout
    hSCH_Add_Task(task4_update, 0, 1,0); //  tombol userLED ditekan-> LED on 100ms off 3000ms

    /* Start the scheduler */
    hSCH_Start();
    while (1)
    {
        hSCH_Dispatch_Tasks();
    }
	return 0;
}




