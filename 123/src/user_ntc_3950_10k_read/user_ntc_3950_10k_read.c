/*
 * user_ntc_3950_10k_read.c
 *
 *  Created on: 2023年8月11日
 *      Author: admin
 */
#include "user_ntc_3950_10k_read.h"
#include "user_bsp_adc/user_bsp_adc.h"
#include "math.h"
#include <user_bsp_uart/user_bsp_uart.h>
#include "user_lcd_driver/user_lcd_driver.h"
double ntc10k_3950_temp_data(void)
{
   double Rt=0;
   double temp=0;
   //Rp上拉电阻值
   double Rp=10000;
   //T2为25摄氏度，折算为开尔文温度
   double T2=273.15+25;
   double Bx=3950;
   double Ka=273.15;
   double vol=0;
   for(uint8_t i=0;i<10;i++)
   {
       vol+=Read_ADC_Voltage_Value();
   }
   vol=vol/10;
   Rt=vol*10000/(3.29-vol);
   temp=1/(1/T2+(log(Rt/Rp))/Bx)-Ka+0.5;
   DEBUG("room_tempreture=%f",temp);
   return temp;
}
void Read_Temperature_Display()
{
    double temp=0;
    int    temp_integer=0;
    int    temp_decimal = 0;

    temp = ntc10k_3950_temp_data();
    temp=temp*10;
    temp=floor(temp);
    temp_decimal=(int)temp%10;   //小数点后一位
    temp_integer=(int)temp/10;   //整数部分
    LCD_integer_and_decimal_display(7,temp_integer,temp_decimal,20,20,32,16);

}


char* itoa(int num,char* str,int radix)
{/*索引表*/
    char index[]="0123456789ABCDEF";
    unsigned int unum;/*中间变量*/
    int i=0,j,k;
    /*确定unum的值*/
    if(radix==10&&num<0)/*十进制负数*/
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num;/*其他情况*/
    /*转换*/
    do{
        str[i++]=index[unum%(unsigned)radix];
        unum/=(unsigned)radix;
       }while(unum);
    str[i]='\0';
    /*逆序*/
    if(str[0]=='-')
        k=1;/*十进制负数*/
    else
        k=0;

    for(j=k;j<=(i-1)/2;j++)
    {       char temp;
        temp=str[j];
        str[j]=str[i-1+k-j];
        str[i-1+k-j]=temp;
    }
    return str;
}
