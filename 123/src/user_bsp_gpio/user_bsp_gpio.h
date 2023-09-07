#ifndef _USER_GPIO_H_
#define _USER_GPIO_H_

#include "hal_data.h"

#define POWER_ON     R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_12, BSP_IO_LEVEL_HIGH)
#define POWER_OFF  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_12, BSP_IO_LEVEL_LOW)
#define LED2_OFF    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_00, BSP_IO_LEVEL_LOW)
#define LED2_ON    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_00, BSP_IO_LEVEL_HIGH)
#define LED1_OFF    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_01, BSP_IO_LEVEL_LOW)
#define LED1_ON    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_01, BSP_IO_LEVEL_HIGH)
#define DHT11_DATA_LOW     R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, BSP_IO_LEVEL_LOW)
#define DHT11_DATA_HIGH    R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_00_PIN_02, BSP_IO_LEVEL_HIGH)
#define DHT11_DATA_SET_INPUT  R_IOPORT_PinCfg(&g_ioport_ctrl,BSP_IO_PORT_00_PIN_02,((uint32_t) IOPORT_CFG_PORT_DIRECTION_INPUT))
#define DHT11_DATA_SET_OUTPUT R_IOPORT_PinCfg(&g_ioport_ctrl,BSP_IO_PORT_00_PIN_02,((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_HIGH))
#define test_pin_207_H R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_07, BSP_IO_LEVEL_HIGH)
#define test_pin_207_L R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_02_PIN_07, BSP_IO_LEVEL_LOW)
#define ir_send_ON   (R_PFS->PORT[BSP_IO_PORT_02_PIN_06>>8].PIN[BSP_IO_PORT_02_PIN_06 & 0xFF].PmnPFS = IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_HIGH)
#define ir_send_OFF  (R_PFS->PORT[BSP_IO_PORT_02_PIN_06>>8].PIN[BSP_IO_PORT_02_PIN_06 & 0xFF].PmnPFS = IOPORT_CFG_PORT_DIRECTION_OUTPUT | IOPORT_CFG_PORT_OUTPUT_LOW)

void GPIO_Init();
void Power_Input_Init(void);
bool Power_Input_state_query();

#endif
