/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : GPIO.h
* @Description : None
* @Date        : 2015/10/25
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* 防止重调用 -----------------------------------------------------------------*/
#ifndef __GPIO_CONFIG_H
#define __GPIO_CONFIG_H 
/* 全局宏定义 -----------------------------------------------------------------*/

/* LED ------------------------------------*/
#define LED1_OFF() LED_Control(1,0)
#define LED2_OFF() LED_Control(2,0)
#define LED3_OFF() LED_Control(3,0)

#define LED1_ON()  LED_Control(1,1)
#define LED2_ON()  LED_Control(2,1)
#define LED3_ON()  LED_Control(3,1)

#define _1Khz_Out_ON()   PORTEbits.RE7 = 1
#define _1Khz_Out_OFF()  PORTEbits.RE7 = 0



/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC官方函数库

/* 全局变量包含 ---------------------------------------------------------------*/

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern unsigned char LED_BUS;

/* 全局函数声明 ---------------------------------------------------------------*/  
void GPIO_Config();
void LED_Control(unsigned char _LED_num,unsigned char _switch);


#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
