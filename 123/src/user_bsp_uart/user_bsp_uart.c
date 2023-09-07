/*
 * debug_uart.c
 *
 *  Created on: 2023年6月27日
 *      Author: admin
 */
#include <user_bsp_uart/user_bsp_uart.h>
#include "user_lcd_driver/user_lcd_driver.h"
#include "user_wifi/user_wifi.h"
/* 发送完成标志 */
volatile bool uart1_send_complete_flag = false;
volatile bool uart2_send_complete_flag = false;
volatile bool uart9_send_complete_flag = false;
volatile bool uart1_Receive_COMPLETE_flag=false;
extern wifi_up_load wifi_up_load_now;
uint8_t  Rx1Buffer[100];         //串口1接收buffer;
uint8_t  Rx1_Receive_Count=0;
uint8_t  UART_TO_WIFI_STA=0;
uint8_t  Wifi_state_flag = 0;
uint8_t  wifi_get_weather_init_flag = 0;

void ALL_Uart_Init(void)
{
    debug_uart1_Init();
    User_uart2_Init();
    User_uart9_Init();
}

void debug_uart1_Init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_SCI_UART_Open(&g_uart1_ctrl, &g_uart1_cfg);
    assert(err == FSP_SUCCESS);
}
void User_uart2_Init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_SCI_UART_Open(&g_uart2_ctrl, &g_uart2_cfg);
    assert(err == FSP_SUCCESS);
}
void User_uart9_Init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_SCI_UART_Open(&g_uart9_ctrl, &g_uart9_cfg);
    assert(err == FSP_SUCCESS);
}
//****************DEBUG通讯口*****************//
void User_UART2_Callback(uart_callback_args_t * p_args)
{
    switch (p_args->event)
           {
              case UART_EVENT_RX_CHAR:
              {
                  R_SCI_UART_Write(&g_uart2_ctrl, (uint8_t *)&(p_args->data), 1);
                    break;
              }
              case UART_EVENT_TX_COMPLETE:
              {
                  uart2_send_complete_flag = true;
                    break;
              }
              default:
                    break;
           }
}
//****************与语音通讯*****************//
void User_UART9_Callback(uart_callback_args_t * p_args)
{
    switch (p_args->event)
           {
              case UART_EVENT_RX_CHAR:
              {
                    break;
              }
              case UART_EVENT_TX_COMPLETE:
              {
                   uart9_send_complete_flag = true;
                    break;
              }
              default:
                    break;
           }
}

//****************与WiFi通讯*****************//
void User_UART1_Callback(uart_callback_args_t * p_args)
{
    switch (p_args->event)
       {
          case UART_EVENT_RX_CHAR:
          {
                /* 把串口接收到的数据发送回去 */
              //  R_SCI_UART_Write(&g_uart1_ctrl, (uint8_t *)&(p_args->data), 1);

                if(Rx1_Receive_Count >= 100)  //溢出判断
                  {
                    Rx1_Receive_Count = 0;
                    memset(Rx1Buffer,0x00,sizeof(Rx1Buffer));
                   }else{
                       if(p_args->data==0x5A)
                       {
                           memset(Rx1Buffer,0x00,sizeof(Rx1Buffer));
                           Rx1_Receive_Count = 0;
                       }
                       Rx1Buffer[Rx1_Receive_Count++] = (uint8_t)(p_args->data);   //接收数据转存
                   }
                break;
          }
          case UART_EVENT_TX_COMPLETE:
          {
                uart1_send_complete_flag = true;
                break;
          }
          case UART_EVENT_RX_COMPLETE:
          {
              uart1_Receive_COMPLETE_flag= true;
              break;
          }
          default:
                break;
       }
}
/* 重定向 printf 输出 */
#if defined __GNUC__ && !defined __clang__
int _write(int fd, char *pBuffer, int size); //防止编译警告
int _write(int fd, char *pBuffer, int size)
{
   (void)fd;
   R_SCI_UART_Write(&g_uart2_ctrl, (uint8_t *)pBuffer, (uint32_t)size);
   while(uart2_send_complete_flag == false);
   uart2_send_complete_flag = false;

   return size;
}
#else
int fputc(int ch, FILE *f)
{
   (void)f;
   R_SCI_UART_Write(&g_uart2_ctrl, (uint8_t *)&ch, 1);
   while(uart2_send_complete_flag == false);
   uart2_send_complete_flag = false;

   return ch;
}
#endif

void Receive_weather_by_UART1()
{
    uint8_t * p;
    if((Rx1Buffer[0]==0x35)&&(Rx1Buffer[1]==0x41))
    {
        UART_TO_WIFI_STA = 0;
        R_SCI_UART_Write(&g_uart2_ctrl, Rx1Buffer, 50);
            while(uart2_send_complete_flag == false);
            uart2_send_complete_flag = false;
            p = Rx1Buffer;
            if((*(p+4)==0x74)&&(*(p+15)==0x3D))
              {
                for(uint8_t i=0;i<6;i++)
                {
                  if( *(p+15+i)==13)
                  {
                      *(p+15+i)= 0x7F;
                      i=9;
                  }
                  DEBUG("lllll=%d,i=%d",*(p+15+i),i);
                }
                display_char16_16(132,92,16,32,WHITE,(char *)(p+16));
              }
            for(uint8_t i=0;i<60;i++)
            {
                //DEBUG("p=%d",*(p+i));
                if((*(p+i)==0x77)&&(*(p+i+4)==0x3D))
                {
                    display_char16_16(132,128,16,32,WHITE,(char *)(p+i+5));
                }
            }
            wifi_get_weather_init_flag=1;
    }else{
    }
}
uint8_t UART1_Receive_Weather_init_flag()
{
  return  wifi_get_weather_init_flag;
}
void    Set_wifi_get_weather_init_flag()
{
    wifi_get_weather_init_flag=0;
}

void Send_get_wifi_state_by_UART1()
{

    uint8_t get_weather_command[5];
    get_weather_command[0]=0x5A;
    get_weather_command[1]=0xA5;
    get_weather_command[2]=0x02;
    get_weather_command[3]=0x5A;
    get_weather_command[4]=0xA5;
    R_SCI_UART_Write(&g_uart1_ctrl, get_weather_command, 5);
    while(uart1_send_complete_flag == false);
    uart1_send_complete_flag = false;
    UART_TO_WIFI_STA = 1;
    Wifi_state_flag = 0;
}
void Send_get_weather_by_UART1()
{
    uint8_t get_weather_command[5];
    get_weather_command[0]=0x5A;
    get_weather_command[1]=0xA5;
    get_weather_command[2]=0x01;
    get_weather_command[3]=0x5A;
    get_weather_command[4]=0xA5;
    R_SCI_UART_Write(&g_uart1_ctrl, get_weather_command, 5);
    while(uart1_send_complete_flag == false);
    uart1_send_complete_flag = false;
    UART_TO_WIFI_STA = 2;
}
void Send_wifi_in_softAP_by_UART1()
{

    uint8_t get_weather_command[5];
    get_weather_command[0]=0x5A;
    get_weather_command[1]=0xA5;
    get_weather_command[2]=0x03;
    get_weather_command[3]=0x5A;
    get_weather_command[4]=0xA5;
    R_SCI_UART_Write(&g_uart1_ctrl, get_weather_command, 5);
    while(uart1_send_complete_flag == false);
    uart1_send_complete_flag = false;
    UART_TO_WIFI_STA = 3;
}
void Receive_wifi_in_softAP_by_UATR1()
{

     if((Rx1Buffer[0]==0x5A)&&(Rx1Buffer[1]==0xA5))
        {
          UART_TO_WIFI_STA = 0;
          if(Rx1Buffer[2]==0xFF&&Rx1Buffer[3]==0xFF)
          {
            display_char16_16(20,164,16,32,WHITE,(char *)("WiFi in_softAP    "));
            DEBUG("Wifi_in_softAP");

          }
        }
}
void Receive_wifi_state_by_UATR1()
{

     if((Rx1Buffer[0]==0x43)&&(Rx1Buffer[1]==0x6f))
        {
            UART_TO_WIFI_STA = 0;
            if((Rx1Buffer[8]==0x66)&&(Rx1Buffer[9]==0x61)&&(Rx1Buffer[10]==0x69)&&(Rx1Buffer[11]==0x6C))
            {
                Wifi_state_flag = 0;
            }else if((Rx1Buffer[8]==0x74)&&(Rx1Buffer[9]==0x72)&&(Rx1Buffer[10]==0x75)&&(Rx1Buffer[11]==0x65))
            {
                Wifi_state_flag = 1;
            }else{

            }
        }else{
        }
}
void Receive_wifi_command_by_UATR1()
{

     if((Rx1Buffer[0]==0x5A)&&(Rx1Buffer[1]==0xA5))
        {
         switch ( Rx1Buffer[2])
           {
             case 1:
                 DEBUG("空调温度设置：%d",Rx1Buffer[3]);
               //  wifi_up_load_now.KT_set_temp=Rx1Buffer[3];
                 break;
             case 2:
                 DEBUG("空调模式设置：%d",Rx1Buffer[3]);
               //  wifi_up_load_now.KT_mode=Rx1Buffer[3];
                 break;
             case 3:
                 DEBUG("空调开关设置：%d",Rx1Buffer[3]);
               //  wifi_up_load_now.KT_power_key=Rx1Buffer[3];
                 break;
           }
        }
}
void WiFi_Uart_Receive_All()
{
    switch(UART_TO_WIFI_STA)
    {
        case 1 :
            Receive_wifi_state_by_UATR1();
            break;
        case 2:
            Receive_weather_by_UART1();
            break;
        case 3:
            Receive_wifi_in_softAP_by_UATR1();
            break;
        default:

            break;
    }
    Receive_wifi_command_by_UATR1();
    Rx1_Receive_Count = 0;
    memset(Rx1Buffer,0x00,sizeof(Rx1Buffer));
}
uint8_t Wifi_state()
{
    uint8_t ret=0;
    uint16_t delay=500;
    do{
        R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
        Receive_wifi_state_by_UATR1();
        delay--;
        if(delay==0)
        {
            ret=0;
            return ret;
        }
    }while((Wifi_state_flag==0)||(UART_TO_WIFI_STA!=0));
    Wifi_state_flag=0;
    ret = 1;
    return ret;

}
void Uart1_send(uint8_t * data,uint8_t size)
{

    R_SCI_UART_Write(&g_uart1_ctrl, data, size);
    while(uart1_send_complete_flag == false);
    uart1_send_complete_flag = false;

}

