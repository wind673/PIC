/**********************************************************************************************
 *   文 件 名：KeyStste.h
 *
 *   调试平台：千豪电磁铁----全波调试板
 *
 *   作    者：唐 江
 *
 *   日    期：2012.12.13
 **********************************************************************************************/
#ifndef __KEYSTATE_H
#define __KEYSTATE_H

/* 包含 --------------------------------------------------------------------------------------*/
#include <xc.h>
#include <p18cxxx.h>
#include "stdint.h"
/* 私有宏 ------------------------------------------------------------------------------------*/
#define MAGNE_KEY_PLC 	  ((Key_StateMachine_Local.KeyCode_Bef == 0xfffe)&&(Key_StateMachine_Local.Key_Num == 1)&&(Key_StateMachine_Local.Key_Mode == 1))
#define DEMAG_KEY_PLC 	  ((Key_StateMachine_Local.KeyCode_Bef == 0xfffd)&&(Key_StateMachine_Local.Key_Num == 1)&&(Key_StateMachine_Local.Key_Mode == 1))

#define MAGNE_KEY_PLC_L   ((Key_StateMachine_Local.KeyCode_Bef == 0xfffe)&&(Key_StateMachine_Local.Key_Num == 1)&&(Key_StateMachine_Local.Key_Mode == 3))
#define DEMAG_KEY_PLC_L   ((Key_StateMachine_Local.KeyCode_Bef == 0xfffd)&&(Key_StateMachine_Local.Key_Num == 1)&&(Key_StateMachine_Local.Key_Mode == 3))
/* 私有结构体 --------------------------------------------------------------------------------*/

/**********************************************************************************************
 *结构体名：__Key_StateMachine	
 *
 *成		员：
 *					uint8_t State_Flag  	记录按键状态标志位
 *					uint8_t Key_Mode    	回传按键模式 
 *					说    明：	“0” 无按键   “1”独立短按键   “2”组合短按键  “3”独立长按键
 *					“4”组合长按键		“5”独立持续按键		“6”组合持续按键
 *					uint16_t KeyCode_Pre	记录当前按键IO状态
 *  				uint16_t KeyCode_Bef	记录前一次按键IO口状态
 *					uint8_t Key_Num       同时按下按键个数
 *					uint8_t Key_Count     长按键、持续按键计数
 *
 *说		明：本状态机支持16个独立按键任意按键组合使用，只需自行定义按键状态即可
 *********************************************************************************************/
typedef struct
{
		volatile uint8_t State_Flag;    //状态标志位
		volatile uint8_t Key_Mode;      //按键模式
		volatile uint16_t KeyCode_Pre;  //按键当前键码
		volatile uint16_t KeyCode_Bef;  //前一次按键键码
		volatile uint8_t Key_Num;       //按键个数  
		volatile uint8_t Key_Count;     //长按键计数
}__Key_StateMachine;
extern __Key_StateMachine Key_StateMachine_Local;
/* 函数声明 ----------------------------------------------------------------------------------*/
void Key_State_Sweep(__Key_StateMachine *Key_State);
#endif

/* 文件结束 ----------------------------------------------------------------------------------*/


