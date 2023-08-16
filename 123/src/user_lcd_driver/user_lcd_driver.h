/*
 * user_lcd_driver.h
 *
 *  Created on: 2023年8月4日
 *      Author: admin
 */

#ifndef USER_LCD_DRIVER_USER_LCD_DRIVER_H_
#define USER_LCD_DRIVER_USER_LCD_DRIVER_H_

#include <user_bsp_uart/user_bsp_uart.h>
#include "hal_data.h"
#include "stdio.h"


/**********SPI引脚分配，连接oled屏，更具实际情况修改*********/

#define SPI_SCK_0  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_02, BSP_IO_LEVEL_LOW)        //P2_0
#define SPI_SCK_1  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_02, BSP_IO_LEVEL_HIGH)
#define SPI_SDA_0  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_01, BSP_IO_LEVEL_LOW)
#define SPI_SDA_1  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_01, BSP_IO_LEVEL_HIGH)
#define SPI_RST_0  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_04, BSP_IO_LEVEL_LOW)
#define SPI_RST_1  R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_04, BSP_IO_LEVEL_HIGH)
#define SPI_DC_0   R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_05_PIN_00, BSP_IO_LEVEL_LOW)
#define SPI_DC_1   R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_05_PIN_00, BSP_IO_LEVEL_HIGH)
#define SPI_CS_0   R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_03, BSP_IO_LEVEL_LOW)
#define SPI_CS_1   R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_01_PIN_03, BSP_IO_LEVEL_HIGH)



#define     RED          0XF800   //红色
#define     GREEN        0X07E0   //绿色
#define     BLUE         0X001F   //蓝色
#define     WHITE        0XFFFF   //白色
#define     BLACK        0x0000   //黑色

#define TFT_COLUMN_NUMBER 320
#define TFT_LINE_NUMBER 240
#define TFT_COLUMN_OFFSET 0
#define PIC_NUM 86408           //图片数据大小

void TFT_init(void);             ////ST7789V2
void TFT_full(unsigned int color);
void TFT_clear(void);
void SPI_SendByte(unsigned  char byte);
void SPI_SendByte_16(unsigned  int byte) ;
void TFT_SEND_DATA_16(unsigned int o_data);
void TFT_SEND_CMD(unsigned char o_command);
void TFT_SEND_DATA(unsigned  char o_data);
void display_char16_16(unsigned int x,unsigned int y,unsigned int width,unsigned int height,
                        uint16_t color,char * p);
void Picture_Display(const unsigned char *ptr_pic);
void show_BJ_Piceute();
void LCD_integer_and_decimal_display(unsigned int len,int temp_integer,int temp_decimal,unsigned int x,unsigned int y,unsigned int height,unsigned int width);
void Judge_temperature_and_humidity_display(unsigned int x,unsigned int y,
                    unsigned int width,unsigned int height,uint16_t color);

#endif /* USER_LCD_DRIVER_USER_LCD_DRIVER_H_ */
