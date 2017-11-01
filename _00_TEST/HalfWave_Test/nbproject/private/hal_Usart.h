/**************************(c) Roon**Start File********************************/
/*=============================================================================
* File   Name : hal_usart.h
* Description : 底层串口驱动文件
* Date        : 2015 - 09 - 16
* By          : 张 飞
* E-mail      : roonmobi@126.com
* Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* Explain     :
*=============================================================================*/
/* 防止递归包含 ---------------------------------------------------------------*/
#ifndef __HAL_USART_H_
#define __HAL_USART_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* 头文件包含 -----------------------------------------------------------------*/
#include "main.h"
     
/* 私有宏定义 -----------------------------------------------------------------*/
/* DE RE 开关位 --------------------------------------------------- */
#define RS485_TX_EN()     PORTCbits.RC2 = 0
#define RS485_RX_EN()     PORTCbits.RC2 = 1
     
/* 传输数据长度 单位byte ------------------------------------------- */
#define RS485_DATALEN       10
     
#define _rn_EN_ALLINT()     INTCON |= 0x80				   /* 使能全局中断     */
#define _rn_DIS_ALLINT()	INTCON &= 0x7f				   /* 禁止全局中断 	  */
#define _rn_EN_PERINT()     INTCON |= 0x40				   /* 使能外设中断     */
#define _rn_DIS_PERINT()	INTCON &= 0xbf				   /* 禁止外设中断 	  */
     
/* 私有变量定义 ---------------------------------------------------------------*/
/* 地址码字节 ---------------------------------------------------------------- */
typedef enum
{
    act_Magnet_Success = 0X01,  //充磁成功
    act_Magnet_Warning,         //充磁报警
    act_Demagnet_Success,       //退磁成功
    act_Demagnet_Warning,       //退磁报警
} CBACTION_ENUM;
     
typedef enum
{
    add_ControlBoard = 0X01,    //主板
    add_Panel,                  //面板
    add_FarPanel,               //远程面板
    add_Handle,                 //手柄
    add_Sensor,                 //传感器板
} ADD_ENUM;

/* 功能码字节 ---------------------------------------------------------------- */
typedef enum
{
    cmd_PANEL_MAGNET = 0X01,   //面板充磁
    cmd_PANEL_DEMAGNET,        //面板退磁
    cmd_PANEL_SEARCH,          //面板查询参数
    cmd_PANEL_MODIFY = 0X04,   //面板修改参数
} PANEL_CMD_ENUM;

typedef enum
{
    cmd_HANDLE_MAGNET = 0X05,   //手柄充磁
    cmd_HANDLE_DEMAGNET,        //手柄退磁
    cmd_HANDLE_SEARCH,          //手柄查询参数
    cmd_HANDLE_MODIFY,          //手柄修改参数
    cmd_HANDLE_MONITOR = 0X09,  //手柄监测
} HANDLE_CMD_ENUM;

typedef enum
{
    cmd_FARPANEL_MAGNET = 0X0A,   //远程面板充磁
    cmd_FARPANEL_DEMAGNET,        //远程面板退磁
    cmd_FARPANEL_SEARCH,          //远程面板查询参数
    cmd_FARPANEL_MODIFY = 0X0D,   //远程面板修改参数
} FARPANEL_CMD_ENUM;

typedef enum
{
    cmd_SENSOR_TILT_WAR = 0X0E,   //传感倾斜警告
    cmd_SENSOR_WEIGH_WAR,         //传感称重警告
    cmd_SENSOR_WEIGH = 0X10,      //传感称重
} FARPANEL_CMD_ENUM;

typedef enum
{
    cmd_CB_SUCCESS = 0X11,      //主板充退磁成功
    cmd_CB_WARNING,             //主板充退磁警告
    cmd_CB_RETV_PARAM,          //主板返回参数
    cmd_CB_RETS_PARAM,          //主板改参成功
    cmd_CB_RETV_MONITOR,        //主板返回监测数据
} CB_CMD_ENUM;
     
/* 串口类型定义 ---------------------------------------------------- */
typedef struct fram_t
{
    uint8_t ucRx_Buf[RS485_DATALEN];    //接收缓冲区
    uint8_t ucTx_Buf[RS485_DATALEN];    //发送缓冲区
    uint8_t ucCnt;                      //字节计数器
    uint8_t ucFlg;                      //接收置位
    uint32_t ulTime;                    //超时时间
} FRAM_T;

FRAM_T RS485Fram;
     
/* 函数声明 -------------------------------------------------------------------*/
void RS485_halInit(void);

void Handle_PtlPackSend(ADD_ENUM _Add, HANDLE_CMD_ENUM _Cmd, uint8_t _ParamNo,\
                            uint16_t _ParamValue, uint8_t _Ch);

void RS485_ReceiveData(void);

void RS485_SendData(uint8_t *_pucBuf, uint8_t _ucLen);

void CB_ProtocolAnalysis(ADD_ENUM _Dev);

void Handle_ProtocolAnalysis(void);

#ifdef __cplusplus
}
#endif

#endif
/**************************(c) Roon**End File**********************************/
