/*
 * user_wifi.h
 *
 *  Created on: 2023年8月9日
 *      Author: admin
 */

#ifndef USER_WIFI_USER_WIFI_H_
#define USER_WIFI_USER_WIFI_H_

#include <user_bsp_uart/user_bsp_uart.h>
#include "hal_data.h"
extern volatile bool uart1_Receive_COMPLETE_flag; //串口1完成标志
extern uint8_t  Rx1Buffer[100];         //串口1接收buffer;
extern uint8_t  Rx1_Receive_Count;      //串口1接收计数；
uint8_t GET_Wifi_State();
uint8_t Wifi_get_weather();
void Wifi_state_inquire();
#endif /* USER_WIFI_USER_WIFI_H_ */
