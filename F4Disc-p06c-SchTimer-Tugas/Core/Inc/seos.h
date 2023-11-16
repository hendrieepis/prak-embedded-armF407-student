/*
 * seos.h
 *
 *  Created on: Aug 25, 2023
 *      Author: hendri
 */

#ifndef INC_SEOS_H_
#define INC_SEOS_H_
void MX_TIM2_Init(uint32_t periode);
void SCH_INIT(uint32_t periode);
void SCH_START(void);
uint8_t SCH_Add_Task(void (* pFunction)(),uint16_t DELAY,uint16_t PERIOD);
void SCH_Dispatch_Tasks(void);
uint8_t SCH_Delete_Task(const uint8_t TASK_INDEX);
void SCH_update(void);
void SCH_Report_Status(void);
#endif /* INC_SEOS_H_ */
