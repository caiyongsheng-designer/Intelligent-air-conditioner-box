/*
 * user_ir_send.c
 *
 *  Created on: 2023年8月22日
 *      Author: admin
 */
#include "user_ir_send.h"
uint16_t gpt0_count=0;

void ir_send_1()                  //bit=1的编码
{
  R_GPT_Start(&g_timer_gpt0_ctrl);
  delay_80us(7);
  R_GPT_Stop(&g_timer_gpt0_ctrl);
  ir_send_OFF;
  delay_80us(21);
}
void ir_send_0()                  //bit=0的编码
{
  R_GPT_Start(&g_timer_gpt0_ctrl);
  delay_80us(7);
  R_GPT_Stop(&g_timer_gpt0_ctrl);
  ir_send_OFF;
  delay_80us(7);
}
void ir_send_init()                        //引导码函数
{
    R_GPT_Start(&g_timer_gpt0_ctrl);
    delay_80us(113);                 //起始发送9ms38K
    R_GPT_Stop(&g_timer_gpt0_ctrl);
    ir_send_OFF;
    delay_80us(56);                  //关闭4.5ms
}
void ir_send_data(uint8_t * p,uint8_t len)
{
    R_GPT_Start(&g_timer_gpt7_ctrl);
    ir_send_init();
    for(uint8_t i=0;i<len;i++)
    {
        for(uint8_t j=0;j<8;j++)
        {
          // DEBUG("*p=%d",*p);
            if(*p&0x80)
            {
                ir_send_1();
              //  DEBUG("....1");
            }else{
                ir_send_0();
              //  DEBUG("....0");
            }
            *p<<=1;
      }
     p++;
    }
    R_GPT_Start(&g_timer_gpt0_ctrl);
    delay_80us(7);
    R_GPT_Stop(&g_timer_gpt0_ctrl);
    R_GPT_Stop(&g_timer_gpt7_ctrl);
}
void GPT_Timing_Init(void)
{
    /* 初始化 GPT0 模块 */
    R_GPT_Open(&g_timer_gpt0_ctrl, &g_timer_gpt0_cfg);
    R_GPT_Open(&g_timer_gpt7_ctrl, &g_timer_gpt7_cfg);

    /* 启动 GPT0 定时器 */
  //  R_GPT_Start(&g_timer_gpt0_ctrl);
}
/* GPT 中断回调函数 */
void gpt0_timing_callback(timer_callback_args_t * p_args)
{
    /* 定时器溢出事件 */
    if (TIMER_EVENT_CYCLE_END == p_args->event)
    {
          if(gpt0_count<=1)
          {
              ir_send_ON;
              gpt0_count++;
          }
           if(gpt0_count>=2)
           {
               ir_send_OFF;
               gpt0_count++;
           }
           if(gpt0_count>=4)
           {
             gpt0_count=0;
           }
    }

}
volatile uint16_t gpt0_count1;
void gpt7_timing_callback(timer_callback_args_t * p_args)
{
    /* 定时器溢出事件 */
    if (TIMER_EVENT_CYCLE_END == p_args->event)
    {
      gpt0_count1--;
    }
}
void delay_80us(uint16_t nTimer)
{
    gpt0_count1=nTimer;
    while(gpt0_count1);
}
