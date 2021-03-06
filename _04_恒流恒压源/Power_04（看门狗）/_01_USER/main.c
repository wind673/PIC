/*******************************(C) COPYRIGHT 2016 WindRises（谢玉伸）*********************************/

/**============================================================================
 * @File_Name   : main.c
 * @Description : 主函数文件
 * @Date         : 2016/2/20
 * @By           : WindRises（谢玉伸）
 * @E_mail      : 1659567673@ qq.com
 * @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
 * @Explain     : 恒流恒压源控制
 *                  1.可以较精确的控制导通时间（时间较大时会有6ms以内的误差）
 *                  2.数码管显示的是0.xx秒(即10ms*数码管数值) 
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include <pic18f67k22.h>                //PIC官方函数库
#include "Config_18F167K22.h"           //配置PIC芯片   
#include "My_Delay.h"                   //粗略延时
#include "My_Types.h"                   //自定义的习惯写法定义
#include "Key.h"                        //按键
#include "Nixie.h"                      //LED显示 
#include "My_Timer.h"                   //定时器（包括中断函数）
#include "Run.h"                        //任务运行的主文件
#include "IR2184.h"                     //恒流恒压源控制芯片
#include "EEPROM.h"                     //EEPROM驱动    

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/

/* 全局变量声明 ---------------------------------------------------------------*/
extern unsigned char IR2184_Num; 
extern unsigned char Watch_Flag;

/* 私有（静态）函数声明 --------------------------------------------------------*

/* 全局函数编写 ---------------------------------------------------------------*/


int main(void)
{
    /* 系统初始化 --------------------------------*/
    Sys_Init();
    
    /* while循环 --------------------------------*/
    while(1) 
    {     
        Watch_Flag = 1;  //清楚看门狗标志标志，定时器喂狗 
        Run();     
        
    }          

return 0;      
}





/*******************************(C) COPYRIGHT 2016 WindRises（谢玉伸）*********************************/
