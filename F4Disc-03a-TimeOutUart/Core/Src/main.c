#include "main.h"
#include "usb_device.h"

#include <stdio.h>
#include "counter.h"
#include "sensor.h"
#include "hardwareinit.h"
#include "checkboard.h"

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
	while (1)
	{

        if(sensorDetected()){
        	CounterUpdate();
        	printf("nilai counter: %d \n\r",counterShow());
        }

        if(resetDetected()){
        	CounterZero();
        	printf("nilai counter: %d \n\r",counterShow());
        }

	}
}


