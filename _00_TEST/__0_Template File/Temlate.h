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

/* �ṹ������ -----------------------------------------------------------------*/ 
/*=-=-=-=-=-=-=-=-=-=-=-=- ����״̬�� =-=-=-=-=-=-=-=-=-=-=-*/
typedef struct KEY_FSM__ 
{
 volatile uchar key_state ; //Ŀǰ����״̬
 volatile uchar key_last ;  //��һ�ΰ���״̬
 volatile uchar key_count ; //��������
}key_FSM__; 

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 

/* ȫ�ֺ������� ---------------------------------------------------------------*/  



#endif
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/
