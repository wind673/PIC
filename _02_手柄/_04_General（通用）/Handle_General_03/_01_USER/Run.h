/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
/**============================================================================
* @File_Name   : Run.h
* @Description : None
* @Date        : 2015/12/9
* @By          : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : 工程的主要运行头文件
*=============================================================================*/

/* 防止重调用 -----------------------------------------------------------------*/
#ifndef __RUN_H
#define __RUN_H 

/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC官方函数库

/* 全局宏定义 -----------------------------------------------------------------*/

/* 结构体声明 -----------------------------------------------------------------*/ 
/* 各种开关结构体 ------------------------------*/
typedef struct  __Switch
{
   unsigned char _1Khz;//1Khz脉冲开关
   unsigned char ADC6;//ADC6采集开关
   unsigned char Usart_OneDate;//发送一组数据
   unsigned char Show_Send_Receive;//显示发送或接收数据 0：接收  1：发送
}__Switch_Def;

/* 各种消息结构体 ------------------------------*/
typedef struct  __Msg
{
   unsigned char Order;            //指令
   unsigned char a_Parameter[4];    //参数数组 :共四个
   unsigned char Hardware_Type;  //硬件类型：手柄，主板，显示板
   unsigned char hand_info;      //消息处理情况： 1已处理，0未处理
   
}__Msg_Def;

/* 枚举类型 -----------------------------------------------------------------*/ 
enum __Hardware_Type
{
    Type_HANDLE = 0, //手柄
    Type_MASTER,     //主板
    Type_SENSOR        
};

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern __Switch_Def gs_Handle_Switch;
extern __Msg_Def gsa_Handle_Msg[10];     //各种消息

/* 全局函数声明 ---------------------------------------------------------------*/  
void Run();
void ManageMessage();
void ShowResult();

#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

