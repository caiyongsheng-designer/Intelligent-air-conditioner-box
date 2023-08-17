/*
 * user_dht11.h
 *
 *  Created on: 2023年8月7日
 *      Author: admin
 */

#ifndef USER_DHT11_USER_DHT11_H_
#define USER_DHT11_USER_DHT11_H_

#include <user_bsp_gpio/user_bsp_gpio.h>
#include <user_bsp_uart/user_bsp_uart.h>
#include "hal_data.h"
#include "stdio.h"

typedef struct DHT11_DATA
{
    uint8_t humdity_integer;//湿度整数
    uint8_t humdity_decimal;//湿度小数
    uint8_t temp_integer ;//温度整数
    uint8_t temp_decimal ;//温度小数
    uint8_t dht11_receive_sucess;//接收成功标志

}dht11_data;


uint8_t DHT11_Read_Byte(void);
dht11_data *DHT11_Read(void);
void DHT11_Init(void);
void Read_H_Display();
void Receive_wifi_state_by_UATR1();
void WiFi_Uart_Receive_All();
#endif /* USER_DHT11_USER_DHT11_H_ */
