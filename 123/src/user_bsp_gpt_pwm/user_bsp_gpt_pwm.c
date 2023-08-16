/*
 * gpt_pwm.c
 *
 *  Created on: 2023年8月7日
 *      Author: admin
 */

#include <user_bsp_gpio/user_bsp_gpio.h>
#include <user_bsp_gpt_pwm/user_bsp_gpt_pwm.h>

timer_info_t info;  //用于获取定时器参数信息
uint32_t period;    //输入捕获计数器的计数周期
/* 保存所测量的PWM信号的信息 */

uint8_t  one_period_flag=0;  //用于表示是否完成对一个完整周期的测量
uint8_t ir_rbuf[100];       //ir 数据接收数组
uint8_t ir_rbuf_count = 0;  //接收数组移位
uint8_t receive_8=0;        //接收的数据
uint8_t reveive_flag=0;     //接收数据记位
uint8_t repetition_count=0; //重复码次数
uint8_t ir_receive_complete=0;
/* GPT初始化函数 */
void GPT_InputCapture_Init(void)
{
    /* 初始化 GPT 模块 */
    R_GPT_Open(&g_timer_gpt9_ctrl, &g_timer_gpt9_cfg);

    /*获取当前参数*/
    (void) R_GPT_InfoGet(&g_timer_gpt9_ctrl, &info);
    /* 获取计数周期：GPT的一个周期的计数次数 */
    period = info.period_counts;

    /* 使能输入捕获 */
    R_GPT_Enable(&g_timer_gpt9_ctrl);

    /* 启动 GPT 定时器 */
    R_GPT_Start(&g_timer_gpt9_ctrl);
}
/* GPT 输入捕获中断回调函数 */
 void gpt9_input_capture_callback(timer_callback_args_t * p_args)
 {
     static uint32_t overflow_times;     //计数器溢出次数
     static uint32_t a_time; // A 上升沿捕获的时间
     static uint32_t b_time; // B 下降沿捕获的时间
     static uint32_t d_time;
     static uint32_t pwm_high_level_time;
     switch(p_args->event)
     {
         /* 捕获到上升沿 -- 有可能是 A 或者 C (A') 位置 */
         case TIMER_EVENT_CAPTURE_A:
             /* A 开始对某个周期进行测量 */
             if (1 == one_period_flag)
             {
                 b_time = p_args->capture + overflow_times * period; //记录捕获的时间 B
                 d_time = p_args->capture;
                 pwm_high_level_time = b_time - a_time;  //计算高电平时间
                 if((7000<=((pwm_high_level_time)/48))&&
                   (((pwm_high_level_time)/48000)<=12000))
                 {
                     one_period_flag++;                                         //引导码开始
                     b_time = 0;
                     a_time = 0;
                     overflow_times = 0;

                 }else{

                     one_period_flag = 0;
                     b_time = 0;
                     a_time = 0;
                     d_time = 0;
                 }
             }else if(3==one_period_flag)
             {
                 b_time = p_args->capture ;
                 overflow_times = 0;
                 one_period_flag ++;
             }
             break;

         /* 捕获到下降沿 -- 是 B 位置 */
         case TIMER_EVENT_CAPTURE_B:
             //如果是在测量周期内检测到下降沿
             if (0 == one_period_flag)
             {
                 a_time = p_args->capture;   //记录捕获的时间 A
                 overflow_times = 0;         //初始化计数器溢出次数
                 one_period_flag ++;         //表示即将完成对某个周期的测量
             }else if(2 == one_period_flag)
             {
                 a_time = p_args->capture+overflow_times * period;   //记录捕获的时间 A
                 if((4200<((a_time-d_time)/48))&&
                      (((a_time-d_time)/48)<=4700))
                    {
                       one_period_flag++;                                         //引导码开始
                       d_time = 0;
                       a_time = 0;
                       overflow_times = 0;
                       ir_rbuf_count = 0;
                       memset(ir_rbuf,0,sizeof(ir_rbuf));           //清空旧的数据帧准备接收新的数据帧
                    }else if((2200<((a_time-d_time)/48))&&         //判断是否为重复码
                            (((a_time-d_time)/48)<=2600)){
                        repetition_count++;
                        d_time = 0;
                        a_time = 0;
                        one_period_flag=0;
                        overflow_times = 0;
                        ir_receive_complete=1;                     //标记ir接收数据完成

                    }else{
                        a_time=0;
                        d_time=0;
                        overflow_times = 0;
                        one_period_flag = 0;
                    }
             }else if(4==one_period_flag)
             {
                 a_time = p_args->capture+overflow_times * period;   //记录捕获的时间 A
                 d_time = (a_time-b_time)/48;
                 if(d_time>300&&d_time<800)
                 {
                     one_period_flag = 3;
                     receive_8 <<=1;
                     reveive_flag++;
                     if(reveive_flag>7)
                     {
                      ir_rbuf[ir_rbuf_count++]=receive_8;
                      reveive_flag = 0;
                      receive_8 = 0;
                     }
                 }else if(d_time>1400&&d_time<1800)
                 {
                     one_period_flag = 3;
                     receive_8 <<=1;
                     receive_8 |= 1;
                     reveive_flag++;
                    if(reveive_flag>7)
                    {
                       ir_rbuf[ir_rbuf_count++]=receive_8;
                       reveive_flag = 0;
                       receive_8 = 0;
                    }
                 }else{

                     one_period_flag = 0;
                 }

             }
             break;

         /* 定时器计数溢出事件 */
         case TIMER_EVENT_CYCLE_END:
             /* 输入捕获期间计数器溢出，则记录溢出次数+1 */
             overflow_times++;
             break;

         default:
             break;
     }
 }
 //此程序只打印红外接收，用来解析空调遥控器编码，为对接收字符做校验，正式使用红外需要对反码补码进行校验
 void ir_receive_data_output(void)
 {
     if(ir_receive_complete==1)
     {
         ir_receive_complete=0;
         for(uint8_t i=0;i<8;i++)
         {
           DEBUG("ir_rbuf=%d,ir_rbuf_count=%d",ir_rbuf[i],i);
         }
     }

 }
