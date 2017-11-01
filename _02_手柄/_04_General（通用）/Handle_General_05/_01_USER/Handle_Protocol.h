/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Handle_Protocol.h
* @Description : 手柄通讯协议头文件
* @Date        : 2015/12/20
* @By          : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* 防止重调用 -----------------------------------------------------------------*/
#ifndef __HANDLE_PROTOCOL_H
#define __HANDLE_PROTOCOL_H 
/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC官方函数库

/* 全局宏定义 -----------------------------------------------------------------*/
#define RS485_OFF()    RG3 = 1 //关闭RS48  1
#define RS485_ON()     RG3 = 0 //打开RS485 0

#define RS485_DATA_LENTH 10    //数据长度

#define RS485_ORDER_BYTE 6     //指令位

#define RS485_DATA_BYTE0 2      //数据位
#define RS485_DATA_BYTE1 3
#define RS485_DATA_BYTE2 4
#define RS485_DATA_BYTE3 5

#define RS485_LOCAL_ADRESS_BYTE  7  //本地地址位
#define RS485_DEST_ADRESS_BYTE   8  //目标地址位

#define CRC_CODE 0xffff         //CRC校验码
#define RS485_START 0xff        //起始码
#define RS485_VACANT 0xaa       //空闲填充数据

/* 结构体声明 -----------------------------------------------------------------*/ 

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern unsigned char ga_RS485_SendBuff[RS485_DATA_LENTH];    //RS485发送数据缓存区
extern unsigned char ga_RS485_ReceiveBuff[RS485_DATA_LENTH]; //RS485接收数据缓存区
extern unsigned char g_RS485_Receive_Flag;                 //RS485接收完成标志
extern unsigned char g_RS485_Byte;                         //RS485字节位

/* 全局函数声明 ---------------------------------------------------------------*/  
unsigned char  RS485_ManageMessage( unsigned char DataBuff[] ,unsigned char date_lenth );
void RS485_AnalysisData(void);
 void VerifyCRC(unsigned char *DataBuff,unsigned char date_lenth);


#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

