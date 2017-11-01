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
#define LED1_OFF() PORTEbits.RE7=1 
#define LED2_OFF() PORTEbits.RE6=1 
#define LED3_OFF() PORTEbits.RE5=1 

#define LED1_ON()  PORTEbits.RE7=0
#define LED2_ON()  PORTEbits.RE6=0 
#define LED3_ON()  PORTEbits.RE5=0 

#define _1Khz_Out_ON()   PORTEbits.RE7 = 1
#define _1Khz_Out_OFF()  PORTEbits.RE7 = 0



/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC官方函数库

/* 全局变量包含 ---------------------------------------------------------------*/
extern uchar LED2_switch ;

/* 全局变量声明 ---------------------------------------------------------------*/ 

/* 全局函数声明 ---------------------------------------------------------------*/  
void GPIO_Config();



#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
