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
#define _user_dht11_temp
typedef struct WIFI_UP_LOAD{
    uint8_t KT_mode;
    uint8_t KT_set_temp;
    uint8_t KT_power_key;
    uint8_t room_temp;
    uint8_t room_humidity;

}wifi_up_load;

extern volatile bool uart1_Receive_COMPLETE_flag; //串口1完成标志
extern uint8_t  Rx1Buffer[100];         //串口1接收buffer;
extern uint8_t  Rx1_Receive_Count;      //串口1接收计数；
uint8_t GET_Wifi_State();
uint8_t Wifi_get_weather();
void Wifi_state_inquire();
void WiFi_data_Upload();
void WiFi_data_Upload_Timing_Report();
#endif /* USER_WIFI_USER_WIFI_H_ */
