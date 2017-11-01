/**********************************************************************************************
 *   �� �� ����KeyStste.h
 *
 *   ����ƽ̨��ǧ�������----ȫ�����԰�
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2012.12.13
 **********************************************************************************************/
#ifndef __KEYSTATE_H
#define __KEYSTATE_H

/* ���� --------------------------------------------------------------------------------------*/
#include <xc.h>
#include <p18cxxx.h>
#include "stdint.h"
/* ˽�к� ------------------------------------------------------------------------------------*/
#define MAGNE_KEY_PLC 	  ((Key_StateMachine_Local.KeyCode_Bef == 0xfffe)&&(Key_StateMachine_Local.Key_Num == 1)&&(Key_StateMachine_Local.Key_Mode == 1))
#define DEMAG_KEY_PLC 	  ((Key_StateMachine_Local.KeyCode_Bef == 0xfffd)&&(Key_StateMachine_Local.Key_Num == 1)&&(Key_StateMachine_Local.Key_Mode == 1))

#define MAGNE_KEY_PLC_L   ((Key_StateMachine_Local.KeyCode_Bef == 0xfffe)&&(Key_StateMachine_Local.Key_Num == 1)&&(Key_StateMachine_Local.Key_Mode == 3))
#define DEMAG_KEY_PLC_L   ((Key_StateMachine_Local.KeyCode_Bef == 0xfffd)&&(Key_StateMachine_Local.Key_Num == 1)&&(Key_StateMachine_Local.Key_Mode == 3))
/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/**********************************************************************************************
 *�ṹ������__Key_StateMachine	
 *
 *��		Ա��
 *					uint8_t State_Flag  	��¼����״̬��־λ
 *					uint8_t Key_Mode    	�ش�����ģʽ 
 *					˵    ����	��0�� �ް���   ��1�������̰���   ��2����϶̰���  ��3������������
 *					��4����ϳ�����		��5��������������		��6����ϳ�������
 *					uint16_t KeyCode_Pre	��¼��ǰ����IO״̬
 *  				uint16_t KeyCode_Bef	��¼ǰһ�ΰ���IO��״̬
 *					uint8_t Key_Num       ͬʱ���°�������
 *					uint8_t Key_Count     ��������������������
 *
 *˵		������״̬��֧��16�������������ⰴ�����ʹ�ã�ֻ�����ж��尴��״̬����
 *********************************************************************************************/
typedef struct
{
		volatile uint8_t State_Flag;    //״̬��־λ
		volatile uint8_t Key_Mode;      //����ģʽ
		volatile uint16_t KeyCode_Pre;  //������ǰ����
		volatile uint16_t KeyCode_Bef;  //ǰһ�ΰ�������
		volatile uint8_t Key_Num;       //��������  
		volatile uint8_t Key_Count;     //����������
}__Key_StateMachine;
extern __Key_StateMachine Key_StateMachine_Local;
/* �������� ----------------------------------------------------------------------------------*/
void Key_State_Sweep(__Key_StateMachine *Key_State);
#endif

/* �ļ����� ----------------------------------------------------------------------------------*/


