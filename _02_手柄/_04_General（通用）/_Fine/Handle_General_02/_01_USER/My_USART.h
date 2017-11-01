/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : My_USART.h
* @Description : ����ͨѶͷ�ļ�
* @Date        : 2015/10/25
* @By          : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* ��ֹ�ص��� -----------------------------------------------------------------*/
#ifndef __MY_USART_H
#define __MY_USART_H 
/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC�ٷ�������

/* ȫ�ֺ궨�� -----------------------------------------------------------------*/
#define RS485_OFF()    RG3 = 1 //�ر�RS48  1
#define RS485_ON()    RG3 = 0  //��RS485 0
#define RS485DATA_LENTH 10
#define CRC_CODE 0xffff
#define RS485_START 0xff

/* �ṹ������ -----------------------------------------------------------------*/ 

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 
extern unsigned char RS485_SendBuff[RS485DATA_LENTH];
extern unsigned char RS485_ReceiveBuff[RS485DATA_LENTH];
extern unsigned char RS485_Receive_Flag;
extern unsigned char RS485_Num;

/* ȫ�ֺ������� ---------------------------------------------------------------*/  
void RS485_Init();
void Write2USART(char data);
void RS485_Send_Date(unsigned char *date_dress, unsigned char date_lenth);
unsigned char  RS485_Message_Manage( unsigned char DataBuff[] ,unsigned char date_lenth );


#endif
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

