/**********************************************************************************************
 *   �� �� ����message.c
 *
 *   ����ƽ̨��ǧ�������----�°�벨���԰�
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2014.12.12
 **********************************************************************************************/

/* ���� --------------------------------------------------------------------------------------*/
#include "message.h"
/* ˽�к� ------------------------------------------------------------------------------------*/

/* ˽�б��� ----------------------------------------------------------------------------------*/
volatile uint32_t Message;
extern uint16_t Spacing_Count;
extern volatile uint8_t g_ucMagFlg;

uint8_t MAGNE_Flag = 0; //0��ʾ��ţ�1��ʾ�˴�
extern __Parameter Parameter[PARAM_NUM+1];
const uint8_t Gears[16] = {0x7d,0x60,0x57,0x76,0x6a,0x3e,0x3f,0x70,
						   0x7f,0x7e,0x7b,0x2f,0x1d,0x67,0x1f,0x1b}; 
/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/* ˽�к������� ------------------------------------------------------------------------------*/

/* ˽�к���ģ�� ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *��    �ƣ�void Message_Send(void)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    ������Ϣ����
 *********************************************************************************************/
void Message_Send(void)
{
/* �����Ϣ ---------------------------------------------------------------------------------*/
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
/* �˴���Ϣ ---------------------------------------------------------------------------------*/
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
 *��    �ƣ�void Message_Manage(void)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    ������Ϣ����
 *********************************************************************************************/
void Message_Manage(void)
{
	uint8_t i;
/* �����Ϣ ---------------------------------------------------------------------------------*/
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
				//Order_Send(6,2);   //��ž���
			}
			else
			{
				//Order_Send(8,2);   //������
			}
		}
/* �˴���Ϣ ---------------------------------------------------------------------------------*/
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
		
/* ��ųɹ���Ϣ -----------------------------------------------------------------------------*/
		if(Message & MESSAGE_MAGNET_FINISH)
		{
			Relay_Warn_Cancle;
			MAGNE_FINIST_LED_ON;
		}
		else if(!(Message & MESSAGE_MAGNET_WARN))
		{
			MAGNE_FINIST_LED_OFF;
		}
/* �˴ųɹ���Ϣ -----------------------------------------------------------------------------*/
		if(Message & MESSAGE_DEMAGE_FINISH)
		{
			Relay_Warn_Cancle;
			DEMAG_FINIST_LED_ON;
		}
		else if(!(Message & MESSAGE_DEMAGE_WARN))
		{
			DEMAG_FINIST_LED_OFF;
		}
/* ϵͳ���� ---------------------------------------------------------------------------------*/
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

/* �ļ����� ---------------------------------------------------------------------------------*/



