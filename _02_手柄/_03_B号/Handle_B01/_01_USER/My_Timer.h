/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : My_Timer.h
* @Description : 定时器头文件
* @Date        : 2015/10/25
* @By          : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* 防止重调用 -----------------------------------------------------------------*/
#ifndef __MY_TIMER_H 
#define __MY_TIMER_H 
/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"           
#include <pic18f67k22.h>                //PIC官方函数库
#include <timers.h>
#include "Key.h"
/* 全局宏定义 -----------------------------------------------------------------*/

/* 结构体声明 -----------------------------------------------------------------*/ 
typedef struct  __Switch
{
   unsigned char _1Khz;//1Khz脉冲开关
   unsigned char ADC6;//ADC6采集开关
   unsigned char Usart_OneDate;
   
}__Switch_Def;


/* 全局变量声明 ---------------------------------------------------------------*/ 
extern unsigned long int Timer_Cyc;
extern __Switch_Def Handle_01_Switch;

/* 全局函数声明 ---------------------------------------------------------------*/  
void Timer0_Init(void);
void SetTimer0(uint _tmr);

#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

