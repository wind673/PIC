/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
/**============================================================================
* @File_Name   : My_ADC.h
* @Description : None
* @Date        : 2015/12/5
* @By          : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 -----------------------------------------------------------------*/
#ifndef __MY_ADC_H
#define __MY_ADC_H

/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC官方函数库

/* 全局宏定义 -----------------------------------------------------------------*/

/* 结构体声明 -----------------------------------------------------------------*/ 

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern volatile float ADC6_Buff;

/* 全局函数声明 ---------------------------------------------------------------*/  
void ADC6_Init();
void Get_ADC6();

#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

