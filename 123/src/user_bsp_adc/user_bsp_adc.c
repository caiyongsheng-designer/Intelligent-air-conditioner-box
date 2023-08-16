/*
 * user_adc.c
 *
 *  Created on: 2023年8月3日
 *      Author: admin
 */
#include <user_bsp_adc/user_bsp_adc.h>
#include <user_bsp_uart/user_bsp_uart.h>
#include "stdio.h"
#include "string.h"


void ADC_Init(void)
{
   fsp_err_t err;
   err = R_ADC_Open(&g_adc0_ctrl, &g_adc0_cfg);
   err = R_ADC_ScanCfg(&g_adc0_ctrl, &g_adc0_channel_cfg);
   assert(FSP_SUCCESS == err);
}

//ADC转换完成标志位
volatile bool scan_complete_flag = false;

void adc_callback(adc_callback_args_t * p_args)
{
   FSP_PARAMETER_NOT_USED(p_args);
   scan_complete_flag = true;
}

/* 进行ADC采集，读取ADC数据并转换结果 */
double Read_ADC_Voltage_Value(void)
{
   uint16_t adc_data;
   double a0;

   (void)R_ADC_ScanStart(&g_adc0_ctrl);
   while (!scan_complete_flag) //等待转换完成标志
   {
      ;
   }
   scan_complete_flag = false; //重新清除标志位

   /* 读取通道8数据 */
   R_ADC_Read(&g_adc0_ctrl, ADC_CHANNEL_8, &adc_data);
   /* ADC原始数据转换为电压值（ADC参考电压为3.3V） */
  // DEBUG("%d",adc_data);
   a0 = (double)(adc_data*3.3/4095);

   return a0;
}

