/**********************************************************************************************
 *   文 件 名：GPIO.h
 *
 *   调试平台：PIC18FXX 开发平台
 *
 *   作    者：唐 江
 *
 *   日    期：2013.10.8
 **********************************************************************************************/

#ifndef ___GPIO_H
#define ___GPIO_H

/* 包含 --------------------------------------------------------------------------------------*/
#include <xc.h>
#include <p18cxxx.h>
#include "pic18f67k22.h"
#include "stdint.h"
/* 私有宏 ------------------------------------------------------------------------------------*/
#define Relay_COM_ON          {PORTDbits.RD0 = 1;PORTDbits.RD1 = 1;}   
														
#define Relay_COM_OFF         {PORTDbits.RD0 = 0;PORTDbits.RD1 = 0;}
														

#define Relay_Channel_1_ON    {PORTEbits.RE0 = 1;}														
#define Relay_Channel_1_OFF   {PORTEbits.RE0 = 0;}
														
#define Relay_Channel_2_ON    {PORTEbits.RE1 = 1;}														
#define Relay_Channel_2_OFF   {PORTEbits.RE1 = 0;}


#define Relay_Magne_Tick      {PORTDbits.RD5 = 1;}
#define Relay_Demag_Tick      {PORTDbits.RD5 = 0;}

#define Relay_Warn_Tick       {PORTDbits.RD4 = 1;}
#define Relay_Warn_Cancle     {PORTDbits.RD4 = 0;}

/* 私有结构体 --------------------------------------------------------------------------------*/

/* 函数声明 ----------------------------------------------------------------------------------*/
void GPIO_Init(void);
#endif

/* 文件结束 ----------------------------------------------------------------------------------*/





