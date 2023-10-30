/*
 * seos.h
 *
 *  Created on: Aug 25, 2023
 *      Author: hendri
 */

#ifndef INC_SEOS_H_
#define INC_SEOS_H_

// *** edit only in this line below **
#define hSCH_MAX_TASKS 3
#define RETURN_NORMAL  0
#define RETURN_ERROR  1
//************************************

// Error codes
//----------------------------------------------------------------------
#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)


void MX_TIM2_Init(uint32_t periode);
void hSCH_init(uint32_t periode);
void hSCH_Start(void);
uint8_t hSCH_Add_Task(void (* pFunction)(),uint16_t DELAY,uint16_t PERIOD,uint8_t Co_op);
void hSCH_Dispatch_Tasks(void);
uint8_t hSCH_Delete_Task(uint8_t Task_index);
void hSCH_Update(void);
void hSCH_Report_Status(void);


#endif /* INC_SEOS_H_ */
