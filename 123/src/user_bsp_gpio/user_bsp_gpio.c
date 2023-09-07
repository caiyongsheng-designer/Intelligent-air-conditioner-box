#include <user_bsp_gpio/user_bsp_gpio.h>
#include "user_bsp_uart/user_bsp_uart.h"
volatile bool Power_input_flag = false;
void GPIO_Init()
{
      R_IOPORT_Open(&g_ioport_ctrl,g_ioport.p_cfg);

}
/*  外部中断初始化函数 */
void Power_Input_Init(void)
{
   fsp_err_t err = FSP_SUCCESS;

   /* Open ICU module */
   err = R_ICU_ExternalIrqOpen(&g_external_irq4_ctrl, &g_external_irq4_cfg);
   /* 允许中断 */
   err = R_ICU_ExternalIrqEnable(&g_external_irq4_ctrl);
   assert(err == FSP_SUCCESS);
}

void power_in_irq_callback(external_irq_callback_args_t *p_args)
{
    bsp_io_level_t  state;
    uint8_t i=0;
   /* 判断中断通道 */
   if (4 == p_args->channel)
   {
      Power_input_flag = true;   // 按键KEY1_SW2按下
      do  //等待按键释放
        {
          R_BSP_SoftwareDelay(100,BSP_DELAY_UNITS_MILLISECONDS);
          R_IOPORT_PinRead(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_11, &state);
          i++;
          if(i>40)
          {
              DEBUG("发送wifi配网指令");
              Send_wifi_in_softAP_by_UART1();
              break;
          }
        } while (BSP_IO_LEVEL_LOW == state);
      if(i>40)
      {
          ;
      }else{
          POWER_OFF;
      }

   }
}
 bool Power_Input_state_query()
{
   return Power_input_flag;
}
