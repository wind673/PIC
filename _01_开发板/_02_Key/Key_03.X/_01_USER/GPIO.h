/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : GPIO_Config.h
* @Description : None
* @Date        : 2015/10/25
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* ��ֹ�ص��� -----------------------------------------------------------------*/
#ifndef __GPIO_CONFIG_H
#define __GPIO_CONFIG_H 
/* ȫ�ֺ궨�� -----------------------------------------------------------------*/

/* LED ------------------------------------*/
#define LED1_OFF PORTEbits.RE2=1; 
#define LED2_OFF PORTEbits.RE3=1; 
#define LED3_OFF PORTEbits.RE4=1; 
#define LED4_OFF PORTEbits.RE5=1; 

#define LED1_ON  PORTEbits.RE2=0; 
#define LED2_ON  PORTEbits.RE3=0; 
#define LED3_ON  PORTEbits.RE4=0; 
#define LED4_ON  PORTEbits.RE5=0; 

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "My_Types.h"

/* ȫ�ֱ������� ---------------------------------------------------------------*/
extern uchar LED_switch ;

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 

/* ȫ�ֺ������� ---------------------------------------------------------------*/  
void GPIO_Config();
unsigned char  LED_Control(unsigned char _Dx,unsigned char _switch);




#endif
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/
