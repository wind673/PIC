/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : main.c
* @Description : 主函数文件
* @Date         : 2015/10/25
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include <pic18f67k22.h>                //PIC官方函数库
#include "Config_18F167K22.h"           //配置PIC芯片   
#include "My_Delay.h"                   //延时
#include "GPIO.h"                       //GPIO口的配置
#include "My_Types.h"                   //自定义的习惯写法定义
#include "Key.h"                        //简写定义
#include "TM1640.h"                     //LED显示
#include "My_ADC.h"                     //ADC

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/

/* 全局变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*

/* 全局函数编写 ---------------------------------------------------------------*/


int main(void)
{
    float num = 0;
    GPIO_Config();    //LED灯
    Key_Init();       //按键
    Timer0_Init();    //定时器
    Init_TM1640(); 
    ADC6_Init();
     
while(1)
{
    TM1640_Show_Decimal( ADC6_Buff );            
                                                            
    delay_ms(200);                               
}
    
    
return 0;      
}





/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
