/*
 * user_dht11.c
 *
 *  Created on: 2023年8月7日
 *      Author: admin
 */
#include <user_DHT11/user_dht11.h>
#include "user_lcd_driver/user_lcd_driver.h"
#include "user_wifi/user_wifi.h"
extern wifi_up_load wifi_up_load_now;
void DHT11_Init(void)
{
   DHT11_DATA_SET_OUTPUT;
   DHT11_DATA_HIGH;
   R_BSP_SoftwareDelay(1000U, BSP_DELAY_UNITS_MILLISECONDS);
   DHT11_DATA_LOW;
   R_BSP_SoftwareDelay(18,BSP_DELAY_UNITS_MILLISECONDS);
   DHT11_DATA_HIGH;
   DHT11_DATA_SET_INPUT;
   test_pin_207_L;
}
dht11_data * DHT11_Read(void)
{
    dht11_data * dht11_data1 = (dht11_data*)malloc(sizeof(dht11_data));
    DHT11_Init();
    bsp_io_level_t state;
    uint8_t delay_dht = 100;
    uint8_t dht11_check ;//校验值
    do{
      delay_dht--;
      if (!delay_dht)
      {
          DEBUG("读初始高电平拉低失败");
          dht11_data1->dht11_receive_sucess=0;
          return dht11_data1;
      }
      R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MICROSECONDS);
      R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, &state);
    }while(state == BSP_IO_LEVEL_HIGH);
    delay_dht = 200;
    do{
       delay_dht--;
        if (!delay_dht)
        {
           DEBUG("读初始低电平拉高失败");
           dht11_data1->dht11_receive_sucess=0;
           return dht11_data1;
         }
        R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MICROSECONDS);
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, &state);
      }while(state == BSP_IO_LEVEL_LOW);
    delay_dht = 200;
    do{
            delay_dht--;
            if (!delay_dht)
            {
               DEBUG("读从机高电平拉低开始读数失败");
               dht11_data1->dht11_receive_sucess=0;
               return dht11_data1;
            }
            R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MICROSECONDS);
            R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, &state);
          }while(state == BSP_IO_LEVEL_HIGH);
    dht11_data1->humdity_integer = DHT11_Read_Byte();
    dht11_data1->humdity_decimal = DHT11_Read_Byte();
    dht11_data1->temp_integer = DHT11_Read_Byte();
    dht11_data1->temp_decimal = DHT11_Read_Byte();
    dht11_check = DHT11_Read_Byte();

   if (((dht11_data1->humdity_integer+dht11_data1->humdity_decimal
        +dht11_data1->temp_integer+dht11_data1->temp_decimal)&0xff)==dht11_check)
   {
       dht11_data1->dht11_receive_sucess = 1;
#ifdef user_dht11_temp
       wifi_up_load_now.room_temp = dht11_data1->temp_integer;
#endif
       wifi_up_load_now.room_humidity = dht11_data1->humdity_integer;
       return dht11_data1;
   } else{

       dht11_data1->dht11_receive_sucess = 0;
       return dht11_data1;
   }
}
uint8_t DHT11_Read_Byte(void)
{
    uint8_t ans=0;
    bsp_io_level_t state;
    uint8_t delay_dht = 100;
    for(uint8_t i=0 ;i<8;i++)
    {
        ans <<= 1;
        delay_dht = 100;
        do{
            delay_dht--;
            if (!delay_dht)
            return 0;
            R_BSP_SoftwareDelay(1,BSP_DELAY_UNITS_MICROSECONDS);
            R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, &state);
           }while(state == BSP_IO_LEVEL_LOW);
        R_BSP_SoftwareDelay(28,BSP_DELAY_UNITS_MICROSECONDS);
        R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, &state);
        if (state==BSP_IO_LEVEL_HIGH)
            ans |= 1;
            test_pin_207_H;
            test_pin_207_L;
           do{
               R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, &state);
             }while(state==BSP_IO_LEVEL_HIGH);
        }
    return ans;
}
void Read_H_Display()
{
     dht11_data * dht11_data1 = DHT11_Read();
     if(dht11_data1->dht11_receive_sucess==1)
     {
        LCD_integer_and_decimal_display(7, dht11_data1->humdity_integer,
                                        dht11_data1->humdity_decimal, 20, 56, 32, 16);
     }
    free(dht11_data1);
}


