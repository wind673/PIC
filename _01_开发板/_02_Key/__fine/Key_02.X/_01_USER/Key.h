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

/* 全局宏定义 -----------------------------------------------------------------*/
/*=-=-=-=-=-=-=-=-=-=-=-=- 按键状态 =-=-=-=-=-=-=-=-=-=-=-*/
#define KEY_default 0x00   //无状态 
#define KEY_short   0x01   //短按
#define KEY_double  0x02   //连按
#define KEY_hold    0x03   //长按
#define KEY_busy    0x04   //忙碌
#define KEY_group   0xff   //组合

/*=-=-=-=-=-=-=-=-=-=-=-=- 组合按键 =-=-=-=-=-=-=-=-=-=-=-*/
#define KEY_1_2     (0x03)   //key1和2组合 0000 0011
#define KEY_1_3     (0x05)   //key1和3组合 0000 0101
#define KEY_1_4     (0x09)   //key1和4组合 0000 1001
#define KEY_2_3     (0x06)   //key2和3组合 0000 0110
#define KEY_2_4     (0x0a)   //key2和4组合 0000 1010
#define KEY_3_4     (0x0c)   //key3和4组合 0000 1100

/*=-=-=-=-=-=-=-=-=-=-=-=- 按键时间长度 =-=-=-=-=-=-=-=-=-=-=-*/
#define KEY_short_Time    5     // 5x定时器周期 = 50ms (大于50ms的才是短按)
#define KEY_hold_Time     50     // 500ms    （大于500ms的才是长按）

/* 结构体声明 -----------------------------------------------------------------*/ 
/*=-=-=-=-=-=-=-=-=-=-=-=- 按键状态机结构体 =-=-=-=-=-=-=-=-=-=-=-*/
typedef struct 
{
 volatile uchar key_state ; //目前按键状态总线
 volatile uchar key_FSM[4] ; //状态机状态
 volatile uchar key_group ; //按键组合
 volatile uchar key[4] ; //RC2~5计数
}__Def_Key_FSM; 

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern __Def_Key_FSM Local_Key_FSM;
extern unsigned long int Timer_Cyc;

/* 全局函数声明 ---------------------------------------------------------------*/  
void Key_Init(void);
void Key_FSM_Scan(void);
void Key_FSM_Reset(void);//状态机复位
unsigned char Key_FSM_Read( unsigned char key_num);

#endif
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/



