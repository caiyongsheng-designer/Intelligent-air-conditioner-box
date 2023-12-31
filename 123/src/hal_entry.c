#include <user_bsp_adc/user_bsp_adc.h>
#include <user_bsp_gpio/user_bsp_gpio.h>
#include <user_bsp_gpt_pwm/user_bsp_gpt_pwm.h>
#include <user_bsp_rtc/user_bsp_rtc.h>
#include <user_bsp_uart/user_bsp_uart.h>
#include <user_DHT11/user_dht11.h>
#include <user_bsp_SysTick/user_bsp_SysTick.h>
#include "hal_data.h"
#include "stdio.h"
#include "user_lcd_driver/user_lcd_driver.h"
#include <user_ntc_3950_10k_read/user_ntc_3950_10k_read.h>
#include "user_ir_send/user_ir_send.h"
FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
void System_Init();
uint16_t Systime_100MS;
uint16_t Systime_1S;
FSP_CPP_FOOTER
/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    /* TODO: add your own code here */
  System_Init();
  DEBUG("程序现在开始\r\n");
while(1)
{
    TaskProcess();
}
#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}
void System_Init()
{

    GPIO_Init();
    POWER_ON;
    ALL_Uart_Init();       //uart1初始化函数
    RTC_Init();            //RTC启动，1S中断1次，RTC时钟通过FSP设置
    ADC_Init();
    TFT_init();
    show_BJ_Piceute();
    GPT_InputCapture_Init();
    //   R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_SECONDS);
    display_char16_16(20,20,16,32,WHITE,(char *)("ROOM_T:"));
    display_char16_16(20,56,16,32,WHITE,(char *)("ROOM_H:"));
    display_char16_16(20,92,16,32,WHITE,(char *)("OUTD_T:"));
    display_char16_16(20,128,16,32,WHITE,(char *)("OUTD_W:"));
    display_char16_16(20,164,16,32,WHITE,(char *)("System Init Sucess"));
    Read_H_Display();
    Read_H_Display();
    R_BSP_PinAccessEnable ();  //启用对PFS寄存器的访问
    Power_Input_Init();
    GPT_Timing_Init();
    SysTick_Init(10); //初始化系统时钟,设置中断频率为10Hz,100ms进入一次滴答中断
}
/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&g_ioport_ctrl, g_ioport.p_cfg);
    }
}

#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
FSP_CPP_FOOTER

#endif
