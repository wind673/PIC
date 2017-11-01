/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : Key.h
* @Description : None
* @Date        : 2015/10/25
* @By          : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� -----------------------------------------------------------------*/
#ifndef __KEY_H
#define __KEY_H 

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC�ٷ�������

/* ȫ�ֺ궨�� -----------------------------------------------------------------*/

#define KEY_group   0xff   //���
#define KEY_alone   0xfe   //����

/* ��ϰ��� =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
#define KEY_1_2     ((0x01<<0)|(0x01<<1))   //key1��2��� 0000 0011
#define KEY_1_3     ((0x01<<0)|(0x01<<2))   //key1��3��� 0000 0101
#define KEY_1_4     ((0x01<<0)|(0x01<<3))   //key1��4��� 0000 1001
#define KEY_1_5     ((0x01<<0)|(0x01<<4))   //key1��5��� 0001 0001
#define KEY_1_6     ((0x01<<0)|(0x01<<5))  

#define KEY_2_3     ((0x01<<1)|(0x01<<2))  
#define KEY_2_4     ((0x01<<1)|(0x01<<3))   
#define KEY_2_5     ((0x01<<1)|(0x01<<4))   
#define KEY_2_6     ((0x01<<1)|(0x01<<5))  

#define KEY_3_4     ((0x01<<2)|(0x01<<3))   
#define KEY_3_5     ((0x01<<2)|(0x01<<4))   
#define KEY_3_6     ((0x01<<2)|(0x01<<5))

#define KEY_4_5     ((0x01<<3)|(0x01<<4))  
#define KEY_4_6     ((0x01<<3)|(0x01<<5)) 

#define KEY_5_6     ((0x01<<4)|(0x01<<5)) 

/* ����ʱ�䳤�� =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
#define KEY_short_Time    5      // �̰���Сʱ��
#define KEY_hold_Time     60     // ������Сʱ��

/* ����IO�� =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
#define KEY_NUMBER 6     //������Ŀ
#define KEY_1 RC1  
#define KEY_2 RF1
#define KEY_3 RF2
#define KEY_4 RA4
#define KEY_5 RA5
#define KEY_6 RF3

/* �ṹ������ -----------------------------------------------------------------*/ 
/* ����״̬���ṹ�� ------------------------------------*/
typedef struct Key_Struct
{
 volatile uchar key_BUS ; //Ŀǰ����״̬����
 volatile uchar key_group ; //�������
 volatile uchar key_group_state ; //�������״̬
 volatile uint a_key_count[KEY_NUMBER] ; //RC2~5����
 volatile uchar a_key_state[KEY_NUMBER] ; //����״̬
}__Def_Key_FSM; 

/* ö������ -----------------------------------------------------------------*/ 
/* ����״̬ =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/
enum __KEY_TYPE__
{
    KEY_default = 0x00,   //��״̬ 
    KEY_short,            //�̰�
    KEY_double,           //����
    KEY_hold,             //����
    KEY_busy,             //æµ  
    KEY_long              //����  
};

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 
extern __Def_Key_FSM  gs_Local_Key_User;    

/* ȫ�ֺ������� ---------------------------------------------------------------*/  
void Key_Init(void);
void Key_ScanFSM(void);//ɨ��״̬��
void Key_ResetFSM(void);//״̬����λ
void Key_ReadFSM(void); //��ȡ״̬����״̬
void Key_ManageMessage(void); //������Ϣ����

#endif
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/



