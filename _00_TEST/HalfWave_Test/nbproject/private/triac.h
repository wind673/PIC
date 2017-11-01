/**********************************************************************************************
 *   文 件 名：triac.h
 *
 *   调试平台：千豪电磁铁----新版半波调试板
 *
 *   作    者：唐 江
 *
 *   日    期：2015.10.8
 **********************************************************************************************/
#ifndef __TRIAC_H
#define __TRIAC_H

/* 包含 --------------------------------------------------------------------------------------*/
#include "parameter.h"
#include "ADC.h"
#include "message.h"
#include "delay.h"
#include "gpio.h"
#include "pic18f67xx_it.h"
/* 私有宏 ------------------------------------------------------------------------------------*/
#define TRIAC_ACPLS_PORT         PORTCbits.RC3          //过零检测
#define TRIAC_MAGNET_PORT        PORTDbits.RD7          //充磁可控硅端口 QD2
#define TRIAC_DEMAG_PORT         PORTDbits.RD6          //退磁可控硅端口 QD1
/* 私有结构体 --------------------------------------------------------------------------------*/
typedef enum {DEMAG = 0, MAGNET = !DEMAG} EMCC_State;        //充退磁状态
typedef enum {DISABLE = 0, ENABLE = !DISABLE}FunctionalState;
/* 函数声明 ----------------------------------------------------------------------------------*/
void Magne_Demag_Dispose(EMCC_State EMCC_State);
void Relay_Channel_SW(uint8_t Channel,FunctionalState Flag);
#endif

/* 文件结束 ----------------------------------------------------------------------------------*/

