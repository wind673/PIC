/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Master_Protocol.h
* @Description : 手柄通讯协议头文件
* @Date        : 2015/12/20
* @By          : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* 防止重调用 -----------------------------------------------------------------*/
#ifndef __MASTER_PROTOCOL_H
#define __MASTER_PROTOCOL_H 

/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC官方函数库

/* 全局宏定义 -----------------------------------------------------------------*/
/* 数量 ---------------------------------*/
#define DEVICE_NUMBER 10       //设备数量
#define MAGNET_NUMBER 3        //磁通道数
#define INQUIRY_INTERVAL 50    //查询时间间隔
#define MAGNET_CH_NUMBER 8     //磁通道数

/* 操作位 ---------------------------------*/
#define RS485_ORDER_BYTE 6     //指令位
#define RS485_DATA_BYTE0 2     //数据位
#define RS485_DATA_BYTE1 3
#define RS485_DATA_BYTE2 4
#define RS485_DATA_BYTE3 5
#define RS485_LOCAL_ADRESS_BYTE  7  //本地地址位
#define RS485_DEST_ADRESS_BYTE   8  //目标地址位

/* 功能码 ---------------------------------*/
#define CRC_CODE 0xffff         //CRC校验码
#define RS485_START 0xff        //起始码
#define RS485_VACANT 0xaa       //空闲填充数据

/* 全局枚举定义 -----------------------------------------------------------------*/
/* 地址 ---------------------------------------------------*/
enum __Address
{
   
    Address_Master = 0x00,       //主控板
    Address_Sensor ,             //传感器  
    Address_SMPDP ,              //显示板    
    Address_Handle_A = 0x03,     //A号手柄   
    Address_Handle_B ,           //B号手柄
    Address_Handle_C ,           //C号手柄
    Address_Handle_D ,           //D号手柄
    
    RS485_DATA_LENTH,            //器件数量
    Address_All,                 //全局广播        
};

/* 操作指令 ------------------------------------------------*/
enum __Cmd   
{
    /* 操作指令 --------------------------*/
    Cmd_Reset = 0x00,            //重置所有数据到默认状态  
    Cmd_Magnet ,                 //充磁     
    Cmd_Demagnet ,               //退磁      
    Cmd_Inquiry ,                //查询
    
    /* 写入指令 --------------------------*/
    Cmd_Write_Current ,          //写入电流参数
    Cmd_Write_Tilting ,          //写入倾斜参数    
    Cmd_Write_Weight ,           //写入质量参数  
    Cmd_Write_Temp ,             //写入温度参数  
    
    /* 读取指令 --------------------------*/    
    Cmd_Read_Current ,           //读取电流参数     
    Cmd_Read_Tilting ,           //读取倾斜参数    
    Cmd_Read_Weight ,            //读取质量参数  
    Cmd_Read_Temp ,              //读取温度参数   
    
    /* 状态指令 --------------------------*/  
    Cmd_State_Success ,          //成功状态（用于返回操作结果）  
    Cmd_State_Failure ,          //成功状态（用于返回操作结果）  
    Cmd_State_Warning ,          //成功状态（用于返回操作结果）  
    
    
};    

/* 默认参数 ------------------------------------------------*/                              
enum __Default
{
    Default_Current = 0,       //电流默认值
    Default_TiltingX = 0,      //X轴倾斜角度默认值 
    Default_TiltingY = 0,      //Y轴倾斜角度默认值 
    Default_Weight = 0,        //质量默认值     
    Default_Temp = 0,          //温度值默认值 
    
}; 

/* 结构体声明 -----------------------------------------------------------------*/ 

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern unsigned char ga_RS485_SendBuff[RS485_DATA_LENTH];    //RS485发送数据缓存区
extern unsigned char ga_RS485_ReceiveBuff[RS485_DATA_LENTH]; //RS485接收数据缓存区
extern unsigned char g_RS485_Receive_Flag;                 //RS485接收完成标志
extern unsigned char g_RS485_Byte;                         //RS485字节位
extern unsigned char g_Inquiry_Flag;                       //查询标志位

/* 全局函数声明 ---------------------------------------------------------------*/  
unsigned char  RS485_RecogniseMessage( unsigned char DataBuff[] ,unsigned char date_lenth );
void RS485_AnalysisData(void);
void VerifyCRC(unsigned char *DataBuff,unsigned char date_lenth);
void RS485_Inquiry(void);

#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

