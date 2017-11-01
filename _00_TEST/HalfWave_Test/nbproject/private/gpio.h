/**********************************************************************************************
 *   �� �� ����GPIO.h
 *
 *   ����ƽ̨��PIC18FXX ����ƽ̨
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2013.10.8
 **********************************************************************************************/

#ifndef ___GPIO_H
#define ___GPIO_H

/* ���� --------------------------------------------------------------------------------------*/
#include <xc.h>
#include <p18cxxx.h>
#include "pic18f67k22.h"
#include "stdint.h"
/* ˽�к� ------------------------------------------------------------------------------------*/
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

/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/* �������� ----------------------------------------------------------------------------------*/
void GPIO_Init(void);
#endif

/* �ļ����� ----------------------------------------------------------------------------------*/





