/*
 * use_wifi.c
 *
 *  Created on: 2023年8月9日
 *      Author: admin
 */

#include "user_wifi/user_wifi.h"
#include <user_bsp_uart/user_bsp_uart.h>
#include "user_lcd_driver/user_lcd_driver.h"

uint8_t GET_Wifi_State()
{
    uint8_t ret;
    Send_get_wifi_state_by_UART1();
    if(Wifi_state())
    {
        ret = 1;
        DEBUG("Wifi_connect_MCU_true");
    }
    else{
        ret=0;
        DEBUG("Wifi_connect_MCU_fail");
    }
    return ret;
}
uint8_t Wifi_get_weather()
{
    uint8_t ret;
    if(GET_Wifi_State())
    {
     DEBUG("Send get weather command");
     Send_get_weather_by_UART1();

     ret =1 ;
    }else{
        DEBUG("Wifi connect fail");
     ret=0;
    }
    return ret;
}
void Wifi_state_inquire()
{

       Send_get_wifi_state_by_UART1();
       if(Wifi_state())
       {
           display_char16_16(20,164,16,32,WHITE,(char *)("WiFi Connect      "));
           DEBUG("Wifi_connect_MCU_true");
       }
       else{

           display_char16_16(20,164,16,32,WHITE,(char *)("WiFi Disconnect   "));
           DEBUG("Wifi_connect_MCU_fail");
       }
}
