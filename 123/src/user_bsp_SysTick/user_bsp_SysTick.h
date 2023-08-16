/*
 * SysTick.h
 *
 *  Created on: 2023年8月7日
 *      Author: admin
 */

#ifndef USER_BSP_SYSTICK_USER_BSP_SYSTICK_H_
#define USER_BSP_SYSTICK_USER_BSP_SYSTICK_H_

#include "hal_data.h"
typedef enum
{
    SYS_DELAY_UNITS_SECONDS      = 48000000, ///< Requested delay amount is in seconds
    SYS_DELAY_UNITS_MILLISECONDS = 48000,    ///< Requested delay amount is in milliseconds
    SYS_DELAY_UNITS_MICROSECONDS = 48        ///< Requested delay amount is in microseconds
} sys_delay_units_t;

void TaskRemarks(void);
void TaskProcess(void);
void SysTick_Init(uint32_t IT_frequency);
void SysTick_Delay(uint32_t delay, sys_delay_units_t unit);

#endif /* USER_BSP_SYSTICK_USER_BSP_SYSTICK_H_ */
