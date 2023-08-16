/*
 * debug_uart.h
 *
 *  Created on: 2023年6月27日
 *      Author: admin
 */

#ifndef USER_BSP_UART_USER_BSP_UART_H_
#define USER_BSP_UART_USER_BSP_UART_H_

#include "hal_data.h"
#include "stdio.h"

#define __DEBUG__

#ifdef __DEBUG__
#define DEBUG(format,...) printf("File: "__FILE__", Line: %05d: "format"\r\n", __LINE__, ##__VA_ARGS__)
#else
#define DEBUG(format,...)
#endif

void debug_uart1_Init(void);
void User_uart2_Init(void);
void User_uart9_Init(void);
void ALL_Uart_Init(void);
void Send_get_weather_by_UART1();
void Receive_weather_by_UART1();
uint8_t Wifi_state();
void Send_get_wifi_state_by_UART1();
void Receive_wifi_state_by_UATR1();
void WiFi_Uart_Receive_All();
uint8_t UART1_Receive_Weather_init();
#endif /* USER_BSP_UART_USER_BSP_UART_H_ */
