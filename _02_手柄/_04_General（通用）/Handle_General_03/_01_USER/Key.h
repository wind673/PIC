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

#define KEY_group   0xff   //组合
#define KEY_alone   0xfe   //单独

/* 组合按键 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
#define KEY_1_2     ((0x01<<0)|(0x01<<1))   //key1和2组合 0000 0011
#define KEY_1_3     ((0x01<<0)|(0x01<<2))   //key1和3组合 0000 0101
#define KEY_1_4     ((0x01<<0)|(0x01<<3))   //key1和4组合 0000 1001
#define KEY_1_5     ((0x01<<0)|(0x01<<4))   //key1和5组合 0001 0001

#define KEY_2_3     ((0x01<<1)|(0x01<<2))  
#define KEY_2_4     ((0x01<<1)|(0x01<<3))   
#define KEY_2_5     ((0x01<<1)|(0x01<<4))   

#define KEY_3_4     ((0x01<<2)|(0x01<<3))   
#define KEY_3_5     ((0x01<<2)|(0x01<<4))   

#define KEY_4_5     ((0x01<<3)|(0x01<<4))  


/* 按键时间长度 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
#define KEY_short_Time    5      // 5x定时器周期  
#define KEY_hold_Time     60     // 

/* 按键IO口 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
#define KEY_NUMBER 5
#define KEY_1 RE3 
#define KEY_2 RE2 
#define KEY_3 RD6
#define KEY_4 RE4
#define KEY_5 RD7


/* 结构体声明 -----------------------------------------------------------------*/ 
/* 按键状态机结构体 ------------------------------------*/
typedef struct Key_Struct
{
 volatile uchar key_BUS ; //目前按键状态总线
 volatile uchar key_group ; //按键组合
 volatile uchar key_group_state ; //按键组合状态
 volatile uint a_key_count[KEY_NUMBER] ; //RC2~5计数
 volatile uchar a_key_state[KEY_NUMBER] ; //按键状态
}__Def_Key_FSM; 

/* 枚举声明 -----------------------------------------------------------------*/ 
/* 按键状态 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
enum __KEY_TYPE__
{
    KEY_default = 0x00,   //无状态 
    KEY_short,            //短按
    KEY_double,           //连按
    KEY_hold,             //长按
    KEY_busy,             //忙碌  
    KEY_long              //长按  
};

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern __Def_Key_FSM  gs_Local_Key_User;    

/* 全局函数声明 ---------------------------------------------------------------*/  
void Key_Init(void);
void Key_ScanFSM(void);
void Key_ResetFSM(void);//状态机复位
void Key_ReadFSM(void); //读取状态机的状态
void Key_ManageMessage(void); //按键消息处理

#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/



