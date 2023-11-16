/*
 * sensor.h
 *
 *  Created on: Aug 26, 2023
 *      Author: hendri
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

unsigned char sensorDetected(void);
uint8_t resetDetected(void);
uint8_t sensorDetectedTimeout(void);
uint8_t resetDetectedTimeout(void);
#endif /* INC_SENSOR_H_ */
