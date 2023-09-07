/*
 * user_ir_send.h
 *
 *  Created on: 2023年8月22日
 *      Author: admin
 */

#ifndef USER_IR_SEND_USER_IR_SEND_H_
#define USER_IR_SEND_USER_IR_SEND_H_
#include <user_bsp_gpio/user_bsp_gpio.h>
#include <user_bsp_uart/user_bsp_uart.h>
#include "hal_data.h"
#include "stdio.h"

void ir_send_1();
void ir_send_0();
void ir_send_init();
void ir_send_data(uint8_t * p,uint8_t len);
void delay_coustom(uint16_t dly);
void GPT_Timing_Init(void);
void delay_80us(uint16_t nTimer);
#endif /* USER_IR_SEND_USER_IR_SEND_H_ */
