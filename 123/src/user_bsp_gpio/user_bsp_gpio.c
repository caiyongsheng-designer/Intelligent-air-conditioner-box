#include <user_bsp_gpio/user_bsp_gpio.h>

void GPIO_Init()
{
      R_IOPORT_Open(&g_ioport_ctrl,g_ioport.p_cfg);

}
