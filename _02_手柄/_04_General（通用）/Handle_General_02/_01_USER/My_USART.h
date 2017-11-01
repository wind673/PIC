/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : My_USART.h
* @Description : 串口通讯头文件
* @Date        : 2015/10/25
* @By          : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* 防止重调用 -----------------------------------------------------------------*/
#ifndef __MY_USART_H
#define __MY_USART_H 
/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC官方函数库

/* 全局宏定义 -----------------------------------------------------------------*/
#define RS485_OFF()    RG3 = 1 //关闭RS48  1
#define RS485_ON()    RG3 = 0  //打开RS485 0
#define RS485DATA_LENTH 10
#define CRC_CODE 0xffff
#define RS485_START 0xff

/* 结构体声明 -----------------------------------------------------------------*/ 

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern unsigned char RS485_SendBuff[RS485DATA_LENTH];
extern unsigned char RS485_ReceiveBuff[RS485DATA_LENTH];
extern unsigned char RS485_Receive_Flag;
extern unsigned char RS485_Num;

/* 全局函数声明 ---------------------------------------------------------------*/  
void RS485_Init();
void Write2USART(char data);
void RS485_Send_Date(unsigned char *date_dress, unsigned char date_lenth);
unsigned char  RS485_Message_Manage( unsigned char DataBuff[] ,unsigned char date_lenth );


#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

