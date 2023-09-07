/*
 * use_wifi.c
 *
 *  Created on: 2023年8月9日
 *      Author: admin
 */

#include "user_wifi/user_wifi.h"
#include <user_bsp_uart/user_bsp_uart.h>
#include "user_lcd_driver/user_lcd_driver.h"
#include "string.h"
uint8_t wifi_state_display=0;
uint8_t wifi_disconnect_inquire_count=0;
wifi_up_load wifi_up_load_before={0,0,0,0,0};
wifi_up_load wifi_up_load_now={0,0,0,0,0};
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
           DEBUG("Wifi_connect_MCU_true.......inquire");
           if(wifi_state_display)      //因为屏幕刷新太耗费时间，增加判断只有状态变化时才刷新
           {
               wifi_disconnect_inquire_count=0;
           }else{
               wifi_state_display = 1;
               display_char16_16(20,164,16,32,WHITE,(char *)("WiFi Connect      "));
               DEBUG("Wifi_connect_MCU_true");
           }
       }
       else{
           DEBUG("Wifi_connect_MCU_fail.......inquire");
           wifi_disconnect_inquire_count++;
           if(wifi_disconnect_inquire_count>12)
           {
               wifi_disconnect_inquire_count=0;
           }
           if((wifi_state_display==1)&&(wifi_disconnect_inquire_count>10))
             {
               wifi_state_display = 0;
               display_char16_16(20,164,16,32,WHITE,(char *)("WiFi Disconnect   "));
               DEBUG("Wifi_connect_MCU_fail");
              }else{
                      ;
              }
            }
}
void WiFi_data_Upload()
{
    uint8_t send_data[9]={0};
    if((wifi_up_load_now.KT_mode != wifi_up_load_before.KT_mode)
     ||(wifi_up_load_now.KT_power_key != wifi_up_load_before.KT_power_key)
     ||(wifi_up_load_now.KT_set_temp != wifi_up_load_before.KT_set_temp)
     ||(wifi_up_load_now.room_humidity != wifi_up_load_before.room_humidity)
     ||(wifi_up_load_now.room_temp != wifi_up_load_before.room_temp))
    {
        memcpy(&wifi_up_load_before,&wifi_up_load_now,sizeof(wifi_up_load_now));
        DEBUG("KT_mode=%d,KT_power_key=%d,KT_ser_temp=%d,room_humidity=%d,room_temp=%d",
                wifi_up_load_before.KT_mode,wifi_up_load_before.KT_power_key,
                wifi_up_load_before.KT_set_temp,wifi_up_load_before.room_humidity,
                wifi_up_load_before.room_temp);
        send_data[0]=0x5A;
        send_data[1]=0xA5;
        send_data[2]=wifi_up_load_now.KT_power_key;
        send_data[3]=wifi_up_load_now.KT_set_temp;
        send_data[4]=wifi_up_load_now.KT_mode;
        send_data[5]=wifi_up_load_now.room_humidity;
        send_data[6]=wifi_up_load_now.room_temp;
        send_data[7]=0x5A;
        send_data[8]=0xA5;
        Uart1_send(send_data,9);

    }else{
       // DEBUG("wifi_up_load_no_change");
    }
}
void WiFi_data_Upload_Timing_Report()
{
        uint8_t send_data[9]={0};
        send_data[0]=0x5A;
        send_data[1]=0xA5;
        send_data[2]=wifi_up_load_now.KT_power_key;
        send_data[3]=wifi_up_load_now.KT_set_temp;
        send_data[4]=wifi_up_load_now.KT_mode;
        send_data[5]=wifi_up_load_now.room_humidity;
        send_data[6]=wifi_up_load_now.room_temp;
        send_data[7]=0x5A;
        send_data[8]=0xA5;
        Uart1_send(send_data,9);

}
