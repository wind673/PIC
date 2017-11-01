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
#include "My_Types.h"
#include "Key.h"                        //简写定义
//#include "TM1640.h"                     //LED显示
/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/


/* 全局函数编写 ---------------------------------------------------------------*/


int main(void)
{
    char LED3_switch;
    GPIO_Config();    //LED灯
    Key_Init();       //按键
    Timer0_Init();    //定时器
          
while(1)
{
    if( Key_FSM_Read(1) == KEY_short )  LED3_switch = ~LED3_switch;
    if( LED3_switch ) LED3_ON;  else LED3_OFF;
   
    if( Key_FSM_Read( KEY_group ) == KEY_3_5 ) LED2_switch = ~LED2_switch;
    
  
}
    
    
return 0;      
}





/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
