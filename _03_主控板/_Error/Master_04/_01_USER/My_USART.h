/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : My_USART.h
* @Description : ����ͨѶͷ�ļ�
* @Date        : 2015/10/25
* @By          : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : ���ڹ���ʵ��ͷ�ļ�
*=============================================================================*/
/* ��ֹ�ص��� -----------------------------------------------------------------*/
#ifndef __MY_USART_H
#define __MY_USART_H 
/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC�ٷ�������

/* ȫ�ֺ궨�� -----------------------------------------------------------------*/
#define RS485_OFF()    RC0 = 1 //�ر�RS48  1
#define RS485_ON()     RC0 = 0 //��RS485 0

#define RS485_DATA_LENTH 10    //���ݳ���

#define RS485_ORDER_BYTE 6     //ָ��λ

#define RS485_DATA_BYTE0 2      //����λ
#define RS485_DATA_BYTE1 3
#define RS485_DATA_BYTE2 4
#define RS485_DATA_BYTE3 5

#define RS485_LOCAL_ADRESS_BYTE  7  //���ص�ַλ
#define RS485_DEST_ADRESS_BYTE   8  //Ŀ���ַλ

#define CRC_CODE 0xffff         //CRCУ����
#define RS485_START 0xff        //��ʼ��
#define RS485_VACANT 0xaa       //�����������

/* �ṹ������ -----------------------------------------------------------------*/ 

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 
extern unsigned char ga_RS485_SendBuff[RS485_DATA_LENTH];    //RS485�������ݻ�����
extern unsigned char ga_RS485_ReceiveBuff[RS485_DATA_LENTH]; //RS485�������ݻ�����
extern unsigned char g_RS485_Receive_Flag;                 //RS485������ɱ�־
extern unsigned char g_RS485_Byte;                         //RS485�ֽ�λ

/* ȫ�ֺ������� ---------------------------------------------------------------*/  
void RS485_Init();
void Write2USART(char data);
void RS485_SendDate(unsigned char *date_dress, unsigned char date_lenth);
unsigned char  RS485_ManageMessage( unsigned char DataBuff[] ,unsigned char date_lenth );
void RS485_AnalysisData(void);

#endif
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

