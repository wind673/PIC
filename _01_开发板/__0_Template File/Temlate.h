/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
/**============================================================================
* @File_Name   : Key.h
* @Description : None
* @Date        : 2015/10/25
* @By          : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 -----------------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H 

/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC官方函数库

/* 全局宏定义 -----------------------------------------------------------------*/

/* 结构体声明 -----------------------------------------------------------------*/ 
/*=-=-=-=-=-=-=-=-=-=-=-=- 按键状态机 =-=-=-=-=-=-=-=-=-=-=-*/
typedef struct KEY_FSM__ 
{
 volatile uchar key_state ; //目前按键状态
 volatile uchar key_last ;  //上一次按键状态
 volatile uchar key_count ; //按键计数
}key_FSM__; 

/* 全局变量声明 ---------------------------------------------------------------*/ 

/* 全局函数声明 ---------------------------------------------------------------*/  



#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

