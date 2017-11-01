/**********************************************************************************************
 *   文 件 名：delay.h
 *
 *   调试平台：PIC18FXX 开发平台
 *
 *   作    者：唐 江
 *
 *   日    期：2013.10.8
 **********************************************************************************************/

#ifndef __MY_DELAY_H
#define __MY_DELAY_H

/* 包含 --------------------------------------------------------------------------------------*/
#include <xc.h>
#include <p18cxxx.h>
#include "stdint.h"
/* 私有宏 ------------------------------------------------------------------------------------*/

/* 私有结构体 --------------------------------------------------------------------------------*/

/* 函数声明 ----------------------------------------------------------------------------------*/
void delay_us(uint32_t nus);
void delay_ms(uint32_t nms);
#endif

/* 文件结束 ----------------------------------------------------------------------------------*/





