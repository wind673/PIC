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
#define DEVICE_NUMBER 10    //设备数量

/* 结构体声明 -----------------------------------------------------------------*/ 
/* 各种开关结构体 ------------------------------*/
typedef struct  __Switch
{
   unsigned char _1Khz;//1Khz脉冲开关
   unsigned char ADC6;//ADC6采集开关
   unsigned char Usart_OneDate;//发送一组数据
   unsigned char Show_Send_Receive;//显示发送或接收数据 0：接收  1：发送
   unsigned char Relay[3];//继电器
}__Switch_Def;

/* 各种消息结构体 ------------------------------*/
typedef struct  __Msg
{
   unsigned char Order;           //指令
   unsigned char a_Parameter[4]; //参数数组 :共四个
   unsigned char Hardware_Type;  //硬件类型：手柄，主板，显示板
   unsigned char new_info;      //消息处理情况：  0已处理的旧数据，1新数据
}__Msg_Def;

/* 公共数据结构体 ------------------------------*/
typedef struct __ComData
{
    uint  Current;      //电流值
    uchar TiltingX;     //X轴倾斜角度 
    uchar TiltingY;     //Y轴倾斜角度 
    uint  Weight;       //质量
    uchar Temp;         //温度值 
    
}__ComDataDef;

/* 枚举类型 -----------------------------------------------------------------*/ 
enum __Hardware_Type
{
    Type_HANDLE = 0, //手柄
    Type_MASTER,     //主板
    Type_SENSOR        
};

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern __Switch_Def gs_Switch;    //各种开关结构体
extern __Msg_Def gsa_Msg[10];     //各种消息
extern __ComDataDef gs_ComData;   //整个系统的公共数据容器

/* 全局函数声明 ---------------------------------------------------------------*/  
void Run();
void ManageMessage();
void ShowResult();

#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

