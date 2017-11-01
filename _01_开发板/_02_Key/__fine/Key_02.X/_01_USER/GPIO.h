/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : GPIO_Config.h
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
#define LED1_OFF PORTEbits.RE2=1; 
#define LED2_OFF PORTEbits.RE3=1; 
#define LED3_OFF PORTEbits.RE4=1; 
#define LED4_OFF PORTEbits.RE5=1; 

#define LED1_ON  PORTEbits.RE2=0; 
#define LED2_ON  PORTEbits.RE3=0; 
#define LED3_ON  PORTEbits.RE4=0; 
#define LED4_ON  PORTEbits.RE5=0; 

/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"

/* 全局变量包含 ---------------------------------------------------------------*/
extern uchar LED_switch ;

/* 全局变量声明 ---------------------------------------------------------------*/ 

/* 全局函数声明 ---------------------------------------------------------------*/  
void GPIO_Config();
unsigned char  LED_Control(unsigned char _Dx,unsigned char _switch);




#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
