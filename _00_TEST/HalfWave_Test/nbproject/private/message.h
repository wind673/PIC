/**********************************************************************************************
 *   文 件 名：message.h
 *
 *   调试平台：千豪电磁铁----新版半波调试板
 *
 *   作    者：唐 江
 *
 *   日    期：2014.12.12
 **********************************************************************************************/
#ifndef __MESSAGE_H
#define __MESSAGE_H

/* 包含 --------------------------------------------------------------------------------------*/
#include "KeyState.h"
#include "parameter.h"
#include "triac.h"
#include "stdint.h"
/* 私有宏 ------------------------------------------------------------------------------------*/
#define MESSAGE_BASE                         ((uint32_t)(0<<0))     //无消息
#define MESSAGE_MAGNE                        ((uint32_t)(1<<0))     //充磁消息
#define MESSAGE_DEMAG                        ((uint32_t)(1<<1))     //退磁消息
#define MESSAGE_MAGNET_FINISH                ((uint32_t)(1<<2))     //充磁完成消息
#define MESSAGE_DEMAGE_FINISH                ((uint32_t)(1<<3))     //退磁完成消息
#define MESSAGE_MAGNET_WARN                  ((uint32_t)(1<<4))     //充磁警报消息
#define MESSAGE_DEMAGE_WARN                  ((uint32_t)(1<<5))     //退磁警报消息
#define MESSAGE_DERIVE_PARAM                 ((uint32_t)(1<<6))     //参数导入消息
#define MESSAGE_IMPORT_PARAM                 ((uint32_t)(1<<7))     //参数导出消息
#define MESSAGE_ELEC_MONITOR                 ((uint32_t)(1<<8))     //电流监测消息
#define MESSAGE_GEARS_ADD                    ((uint32_t)(1<<9))     //档位加
#define MESSAGE_GEARS_MINUS                  ((uint32_t)(1<<10))    //档位减
#define MESSAGE_SYSTEM_WARN                  ((uint32_t)(1<<11))    //系统警报
#define MESSAGE_PARAM_DATA                   ((uint32_t)(1<<12))    //参数数据导出消息
#define MESSAGE_USART_DATA_UPD               ((uint32_t)(1<<13))    //串口数据更新消息
#define MESSAGE_PARAM_UPD                    ((uint32_t)(1<<14))    //系统参数更新消息


#define MAGNE_FINIST_LED_ON         
#define MAGNE_FINIST_LED_OFF        
#define MAGNE_WARN_LED_ON           

#define DEMAG_FINIST_LED_ON         
#define DEMAG_FINIST_LED_OFF        
#define DEMAG_WARN_LED_ON           

#define SYSTEM_WARN_LED_ON          
#define SYSTEM_WARN_LED_OFF         
/* 私有结构体 --------------------------------------------------------------------------------*/

/* 函数声明 ----------------------------------------------------------------------------------*/
void Message_Send(void);
void Message_Manage(void);
#endif

/* 文件结束 ----------------------------------------------------------------------------------*/


