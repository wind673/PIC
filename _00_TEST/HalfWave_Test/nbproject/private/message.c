/**********************************************************************************************
 *   文 件 名：message.c
 *
 *   调试平台：千豪电磁铁----新版半波调试板
 *
 *   作    者：唐 江
 *
 *   日    期：2014.12.12
 **********************************************************************************************/

/* 包含 --------------------------------------------------------------------------------------*/
#include "message.h"
/* 私有宏 ------------------------------------------------------------------------------------*/

/* 私有变量 ----------------------------------------------------------------------------------*/
volatile uint32_t Message;
extern uint16_t Spacing_Count;
extern volatile uint8_t g_ucMagFlg;

uint8_t MAGNE_Flag = 0; //0表示充磁，1表示退磁
extern __Parameter Parameter[PARAM_NUM+1];
const uint8_t Gears[16] = {0x7d,0x60,0x57,0x76,0x6a,0x3e,0x3f,0x70,
						   0x7f,0x7e,0x7b,0x2f,0x1d,0x67,0x1f,0x1b}; 
/* 私有结构体 --------------------------------------------------------------------------------*/

/* 私有函数声明 ------------------------------------------------------------------------------*/

/* 私有函数模型 ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *名    称：void Message_Send(void)
 *
 *参    数：无
 *
 *返 回 值：无
 *
 *描    述：消息发送
 *********************************************************************************************/
void Message_Send(void)
{
/* 充磁消息 ---------------------------------------------------------------------------------*/
		if(((MAGNE_KEY_PLC && !Parameter[_PLC_KEY_MODE].Value) ||
			(MAGNE_KEY_PLC_L && Parameter[_PLC_KEY_MODE].Value) || (g_ucMagFlg == 1)) && (Spacing_Count == 0))
		{
			Relay_Magne_Tick;   
			Message |= MESSAGE_MAGNE;
			Key_StateMachine_Local.Key_Mode = 0;
            if (g_ucMagFlg == 1)
                g_ucMagFlg = 0;
		}
		else
		{
            if (g_ucMagFlg != 2)
            {
                g_ucMagFlg = 0;
            }
			Message &= ~MESSAGE_MAGNE;
		}
/* 退磁消息 ---------------------------------------------------------------------------------*/
		if(((DEMAG_KEY_PLC && !Parameter[_PLC_KEY_MODE].Value) ||
		   (DEMAG_KEY_PLC_L && Parameter[_PLC_KEY_MODE].Value) || (g_ucMagFlg == 2)) && (Spacing_Count == 0))
		{
			Relay_Demag_Tick;
			Message |= MESSAGE_DEMAG;
			Key_StateMachine_Local.Key_Mode = 0;
            if (g_ucMagFlg == 2)
                g_ucMagFlg = 0;
		}
		else
		{
            if (g_ucMagFlg != 1)
            {
                g_ucMagFlg = 0;
            }
			Message &= ~MESSAGE_DEMAG;
		}
}

/**********************************************************************************************
 *名    称：void Message_Manage(void)
 *
 *参    数：无
 *
 *返 回 值：无
 *
 *描    述：消息处理
 *********************************************************************************************/
void Message_Manage(void)
{
	uint8_t i;
/* 充磁消息 ---------------------------------------------------------------------------------*/
		if(Message & MESSAGE_MAGNE)
		{
			SYSTEM_WARN_LED_OFF;
			MAGNE_FINIST_LED_OFF;
			DEMAG_FINIST_LED_OFF;
			delay_ms(10);
			MAGNE_Flag = 0;
			Magne_Demag_Dispose(MAGNET);
			delay_ms(100);
			if(Message & MESSAGE_MAGNET_WARN)
			{
				//Order_Send(6,2);   //充磁警报
			}
			else
			{
				//Order_Send(8,2);   //充磁完成
			}
		}
/* 退磁消息 ---------------------------------------------------------------------------------*/
		if(Message & MESSAGE_DEMAG)
		{
			SYSTEM_WARN_LED_OFF;
			MAGNE_FINIST_LED_OFF;
			DEMAG_FINIST_LED_OFF;
			delay_ms(10);
			MAGNE_Flag = 1;
			Magne_Demag_Dispose(DEMAG);
			delay_ms(100);
			if(Message & MESSAGE_DEMAGE_WARN)
			{
				//Order_Send(7,2);
			}
			else
			{
				//Order_Send(9,2);
			}
		}
		
/* 充磁成功消息 -----------------------------------------------------------------------------*/
		if(Message & MESSAGE_MAGNET_FINISH)
		{
			Relay_Warn_Cancle;
			MAGNE_FINIST_LED_ON;
		}
		else if(!(Message & MESSAGE_MAGNET_WARN))
		{
			MAGNE_FINIST_LED_OFF;
		}
/* 退磁成功消息 -----------------------------------------------------------------------------*/
		if(Message & MESSAGE_DEMAGE_FINISH)
		{
			Relay_Warn_Cancle;
			DEMAG_FINIST_LED_ON;
		}
		else if(!(Message & MESSAGE_DEMAGE_WARN))
		{
			DEMAG_FINIST_LED_OFF;
		}
/* 系统警报 ---------------------------------------------------------------------------------*/
		if((Message & MESSAGE_SYSTEM_WARN) || (Message & MESSAGE_MAGNET_WARN) || (Message & MESSAGE_DEMAGE_WARN))
		{
			Relay_Warn_Tick;
			SYSTEM_WARN_LED_ON;
		}
		else
		{
			SYSTEM_WARN_LED_OFF;
		}
}

/* 文件结束 ---------------------------------------------------------------------------------*/



