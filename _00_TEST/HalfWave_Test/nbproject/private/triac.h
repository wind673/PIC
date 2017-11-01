/**********************************************************************************************
 *   �� �� ����triac.h
 *
 *   ����ƽ̨��ǧ�������----�°�벨���԰�
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2015.10.8
 **********************************************************************************************/
#ifndef __TRIAC_H
#define __TRIAC_H

/* ���� --------------------------------------------------------------------------------------*/
#include "parameter.h"
#include "ADC.h"
#include "message.h"
#include "delay.h"
#include "gpio.h"
#include "pic18f67xx_it.h"
/* ˽�к� ------------------------------------------------------------------------------------*/
#define TRIAC_ACPLS_PORT         PORTCbits.RC3          //������
#define TRIAC_MAGNET_PORT        PORTDbits.RD7          //��ſɿع�˿� QD2
#define TRIAC_DEMAG_PORT         PORTDbits.RD6          //�˴ſɿع�˿� QD1
/* ˽�нṹ�� --------------------------------------------------------------------------------*/
typedef enum {DEMAG = 0, MAGNET = !DEMAG} EMCC_State;        //���˴�״̬
typedef enum {DISABLE = 0, ENABLE = !DISABLE}FunctionalState;
/* �������� ----------------------------------------------------------------------------------*/
void Magne_Demag_Dispose(EMCC_State EMCC_State);
void Relay_Channel_SW(uint8_t Channel,FunctionalState Flag);
#endif

/* �ļ����� ----------------------------------------------------------------------------------*/

