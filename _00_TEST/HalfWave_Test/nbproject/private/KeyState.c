/**********************************************************************************************
 *   文 件 名：KeyStste.c
 *
 *   调试平台：千豪电磁铁----新版半波
 *
 *   作    者：唐 江
 *
 *   日    期：2012.12.13
 **********************************************************************************************/

/* 包含 --------------------------------------------------------------------------------------*/
#include "KeyState.h"
/* 私有宏 ------------------------------------------------------------------------------------*/
#define LONG_KEY_COUNT  15    		//长按键计数
#define KEY_SHIELD      0xfff0		//需要屏蔽的按键IO口  16个按键需要屏蔽哪个按键只需要将对应位置1
/* 私有变量 ----------------------------------------------------------------------------------*/
__Key_StateMachine Key_StateMachine_Local;
/* 私有结构体 --------------------------------------------------------------------------------*/

/* 私有函数声明 ------------------------------------------------------------------------------*/
static void Key_Num_Get(__Key_StateMachine *Key_State);
/* 私有函数模型 ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *名    称：void Key_State_Sweep(__Key_StateMachine *Key_State)
 *
 *参    数：无
 *
 *返 回 值：无
 *
 *描    述：按键状态机
 *********************************************************************************************/
void Key_State_Sweep(__Key_StateMachine *Key_State)
{
		Key_State->KeyCode_Pre =  ((uint16_t)PORTCbits.RC0<<0)
                                | ((uint16_t)PORTCbits.RC1<<1)
                                | ((uint16_t)PORTAbits.RA4<<2)
                                | ((uint16_t)PORTAbits.RA5<<3)|KEY_SHIELD;
		switch(Key_State->State_Flag)
		{
				case 0:
					if(Key_State->KeyCode_Pre != 0xffff)    //判断是否有按键按下
					{
							Key_State->State_Flag = 1;     			//有按键按下则进入第1级
								Key_State->KeyCode_Bef =  ((uint16_t)PORTCbits.RC0<<0)
                                                        | ((uint16_t)PORTCbits.RC1<<1)
                                                        | ((uint16_t)PORTAbits.RA4<<2)
                                                        | ((uint16_t)PORTAbits.RA5<<3)|KEY_SHIELD;
							Key_Num_Get(Key_State);
							Key_State->Key_Mode = 0;       			//无按键
					}
					else
					{
							Key_State->State_Flag = 0;     			//无按键则停留在第0级
							Key_State->Key_Mode = 0;       			//无按键
					}
					break;
					
				case 1:
					if((Key_State->KeyCode_Pre != 0xffff) && 
						 (Key_State->KeyCode_Pre == Key_State->KeyCode_Bef))    //判断是否有按键按下且与上级按下按键相同
					{
							Key_State->Key_Mode = 0;       //无按键
							Key_State->State_Flag = 1;     //停留在第1级
							Key_State->Key_Count++;        //长按键计数加1
							if(Key_State->Key_Count == 3)       //判断长按键计数等于1
							{
									if(Key_State->Key_Num == 1)
									{
											Key_State->Key_Mode = 1;   //独立短按键
									}
									else if(Key_State->Key_Num > 1)
									{
											Key_State->Key_Mode = 2;   //组合短按键
									}
							}
							if(Key_State->Key_Count == LONG_KEY_COUNT)       //判断是否达到长按键计数值
							{
									if(!(Key_State->Key_Mode))
									{
											if(Key_State->Key_Num == 1)
											{
													Key_State->Key_Mode = 3;    //独立长按键
											}
											else if(Key_State->Key_Num > 1)
											{
													Key_State->Key_Mode = 4;    //组合长按键
											}
									}
									Key_State->Key_Count = 0;                    //长按键计数值清零
									Key_State->State_Flag = 2;                   //满足长按键计数值，进入第2级
							}
					}
					else
					{
							Key_State->Key_Count = 0;				 //长按键计数值清零
							Key_State->State_Flag = 0;	     //返回第0级
							Key_State->Key_Mode = 0;       	 //无按键
					}
					break;
					
				case 2:
					if((Key_State->KeyCode_Pre != 0xffff) && 
						 (Key_State->KeyCode_Pre == Key_State->KeyCode_Bef))   //判断是否有按键按下且与上级按下按键相同
					{
							Key_State->State_Flag = 2; 										//停留在第2级
							if(Key_State->Key_Num == 1)
							{
									Key_State->Key_Mode = 5;    //独立持续按键
							}
							if(Key_State->Key_Num > 1)
							{
									Key_State->Key_Mode = 6;    //组合持续按键
							}
					}
					else
					{
							Key_State->Key_Mode = 0;
							Key_State->State_Flag = 0;
							Key_State->Key_Count = 0;
					}
					break;
		}
}
/**********************************************************************************************
 *名    称：static void Key_Num_Get(__Key_StateMachine *Key_State)
 *
 *参    数：无
 *
 *返 回 值：无
 *
 *描    述：键盘键值获取
 *********************************************************************************************/
static void Key_Num_Get(__Key_StateMachine *Key_State)
{
		uint8_t i;
		Key_State->Key_Num = 0;
		for(i = 0;i < 16;i++)
		{
				Key_State->Key_Num += !((Key_State->KeyCode_Bef >> i) & 0x0001); 
		}
}

/* 文件结束 ---------------------------------------------------------------------------------*/

