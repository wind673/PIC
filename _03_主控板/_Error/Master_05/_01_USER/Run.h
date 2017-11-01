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
#include "Master_Protocol.h"

/* 全局宏定义 -----------------------------------------------------------------*/

/* 结构体声明 -----------------------------------------------------------------*/ 
/* 各种开关结构体 ------------------------------*/
typedef struct  __Switch
{
   unsigned char RS485_Reply;//发送一组数据
   unsigned char Show_Send_Receive;//显示发送或接收数据 0：接收  1：发送
   unsigned char a_Relay[MAGNET_NUMBER];//继电器
   unsigned char Inquiry;//查询
   unsigned char Receive;//接收完一帧数据：1 未接受完：0
   unsigned char Magnet; //充磁
   unsigned char Demagnet;//退磁
    
}__Switch_Def;

/* 各种消息结构体 ------------------------------*/
typedef struct  __Msg
{
   unsigned char new_info;             //消息处理情况：  0已处理的旧数据，1新数据
   unsigned char Magnet_Strength;     //充磁强度
   unsigned char Demagnet_Strength;   //退磁强度
   unsigned char Select_CH;            //通道选择
   unsigned char Source_Dress;        //消息来源地址
   
}__Msg_Def;

/* 公共数据结构体 ------------------------------*/
typedef struct __ComData
{
    uint  a_Current[MAGNET_CH_NUMBER];            //每个通道的电流值
    uchar a_Demagnet_Strength[MAGNET_CH_NUMBER]; //退磁强度
    uchar a_Magnet_Strength[MAGNET_CH_NUMBER];   //充磁强度
    uchar TiltingX;                               //X轴倾斜角度 
    uchar TiltingY;                               //Y轴倾斜角度 
    uint  Weight;                                 //质量
    uchar Temp;                                   //温度值 
    uchar a_Magnet_Switch[MAGNET_NUMBER];        //充磁开关
    uchar Magnet_Flag;                                 //退磁使能
    
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
void ManageIncident();
void ManageMessage();
void ShowResult();

#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
