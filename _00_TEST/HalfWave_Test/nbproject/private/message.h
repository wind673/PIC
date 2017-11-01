/**********************************************************************************************
 *   �� �� ����message.h
 *
 *   ����ƽ̨��ǧ�������----�°�벨���԰�
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2014.12.12
 **********************************************************************************************/
#ifndef __MESSAGE_H
#define __MESSAGE_H

/* ���� --------------------------------------------------------------------------------------*/
#include "KeyState.h"
#include "parameter.h"
#include "triac.h"
#include "stdint.h"
/* ˽�к� ------------------------------------------------------------------------------------*/
#define MESSAGE_BASE                         ((uint32_t)(0<<0))     //����Ϣ
#define MESSAGE_MAGNE                        ((uint32_t)(1<<0))     //�����Ϣ
#define MESSAGE_DEMAG                        ((uint32_t)(1<<1))     //�˴���Ϣ
#define MESSAGE_MAGNET_FINISH                ((uint32_t)(1<<2))     //��������Ϣ
#define MESSAGE_DEMAGE_FINISH                ((uint32_t)(1<<3))     //�˴������Ϣ
#define MESSAGE_MAGNET_WARN                  ((uint32_t)(1<<4))     //��ž�����Ϣ
#define MESSAGE_DEMAGE_WARN                  ((uint32_t)(1<<5))     //�˴ž�����Ϣ
#define MESSAGE_DERIVE_PARAM                 ((uint32_t)(1<<6))     //����������Ϣ
#define MESSAGE_IMPORT_PARAM                 ((uint32_t)(1<<7))     //����������Ϣ
#define MESSAGE_ELEC_MONITOR                 ((uint32_t)(1<<8))     //���������Ϣ
#define MESSAGE_GEARS_ADD                    ((uint32_t)(1<<9))     //��λ��
#define MESSAGE_GEARS_MINUS                  ((uint32_t)(1<<10))    //��λ��
#define MESSAGE_SYSTEM_WARN                  ((uint32_t)(1<<11))    //ϵͳ����
#define MESSAGE_PARAM_DATA                   ((uint32_t)(1<<12))    //�������ݵ�����Ϣ
#define MESSAGE_USART_DATA_UPD               ((uint32_t)(1<<13))    //�������ݸ�����Ϣ
#define MESSAGE_PARAM_UPD                    ((uint32_t)(1<<14))    //ϵͳ����������Ϣ


#define MAGNE_FINIST_LED_ON         
#define MAGNE_FINIST_LED_OFF        
#define MAGNE_WARN_LED_ON           

#define DEMAG_FINIST_LED_ON         
#define DEMAG_FINIST_LED_OFF        
#define DEMAG_WARN_LED_ON           

#define SYSTEM_WARN_LED_ON          
#define SYSTEM_WARN_LED_OFF         
/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/* �������� ----------------------------------------------------------------------------------*/
void Message_Send(void);
void Message_Manage(void);
#endif

/* �ļ����� ----------------------------------------------------------------------------------*/


