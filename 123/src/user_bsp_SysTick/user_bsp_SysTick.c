/*
 * SysTick.c

 *
 *  Created on: 2023年8月7日
 *      Author: admin
 */
#include <user_bsp_SysTick/user_bsp_SysTick.h>
#include <user_bsp_uart/user_bsp_uart.h>
#include <user_ntc_3950_10k_read/user_ntc_3950_10k_read.h>
#include <user_bsp_rtc/user_bsp_rtc.h>
#include "user_wifi/user_wifi.h"

uint32_t IT_Period = 0;
uint32_t IT_nums = 0;

// 任务结构
typedef struct _TASK_COMPONENTS
{
    uint8_t Run;                    // 程序运行标记：0-不运行，1运行
    uint8_t Timer;                  // 计时器
    uint8_t ItvTime;              // 任务运行间隔时间【AKA计时器初始值值】
    void (*TaskHook)(void);        // 要运行的任务函数
} TASK_COMPONENTS;       // 任务定义
static TASK_COMPONENTS TaskComps[] =
{
    {0, 2,  2, WiFi_Uart_Receive_All},            // 间隔200MS运行一次,读WiFi数据
    {0, 10, 10, Read_Temperature_Display},         // 间隔1S运行一次，温度测量
    {0, 20, 20, rtc_minute_30_read},            // 间隔2S,读RTC间隔30Min运行
    {0, 50, 50,Wifi_state_inquire},              //间隔5S,检查WiFi状态
 };
typedef enum _TASK_LIST
{
    TASK_WiFi_Uart_Receive_All,
    TASK_Read_Temperature_Display,
    TASK_rtc_minute_30_read,
    TASK_GET_Wifi_State,
    TASKS_MAX         // 总的可供分配的定时任务数目
} TASK_LIST;
/**
  * @brief  启动系统滴答计时器 SysTick
  * @param  IT_frequency: 滴答计时器每秒的中断次数
  * @retval 无
  */
 void SysTick_Init(uint32_t IT_frequency)
 {
     /* SystemCoreClock在这里默认为48M
      * SystemCoreClock / 1000    1ms中断一次
      * SystemCoreClock / 100000  10us中断一次
      * SystemCoreClock / 1000000 1us中断一次
      */
     IT_Period = SystemCoreClock / IT_frequency;
     uint32_t err = SysTick_Config (IT_Period);
     assert(err==0); //capture error
 }

 /**
 * @brief  延时程序（不好用，滴答中断用作时间片处理）
 * @param  delay: 延时的单位时间
 * @param  unit: 延时的单位
 * @retval 无
 */

 void SysTick_Delay(uint32_t delay, sys_delay_units_t unit)
 {
     uint32_t SumTime = delay * unit; //计算总延时时间(单位为时钟节拍数)
     IT_nums = SumTime/IT_Period;

     while (IT_nums != 0)
     {
       DEBUG("IT_nums=%d",IT_nums);
     }

 }

 /**
 * @brief  SysTick的中断服务函数
 * @param  无
 * @retval 无
 */
 extern void SysTick_Handler(void); //需要先extern声明一下避免编译器警告
 void SysTick_Handler(void)
 {
     TaskRemarks();
 }
 void TaskRemarks(void)
 {
     uint8_t i;

     for (i=0; i<TASKS_MAX; i++)          // 逐个任务时间处理
     {
          if (TaskComps[i].Timer)          // 时间不为0
         {
            TaskComps[i].Timer--;         // 减去一个节拍
            if (TaskComps[i].Timer == 0)       // 时间减完了
            {
              TaskComps[i].Timer = TaskComps[i].ItvTime; // 恢复计时器值，从新下一次
              TaskComps[i].Run = 1;           // 任务可以运行
            }
         }
    }
 }

 void TaskProcess(void)
 {
     uint8_t i;

     for (i=0; i<TASKS_MAX; i++)           // 逐个任务时间处理
     {
          if (TaskComps[i].Run)           // 时间不为0
         {
              TaskComps[i].TaskHook();         // 运行任务
              TaskComps[i].Run = 0;          // 标志清0
         }
     }
 }
