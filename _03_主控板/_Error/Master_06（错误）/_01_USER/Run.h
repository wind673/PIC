/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/
/**============================================================================
* @File_Name   : Run.h
* @Description : None
* @Date        : 2015/12/9
* @By          : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : ���̵���Ҫ����ͷ�ļ�
*=============================================================================*/

/* ��ֹ�ص��� -----------------------------------------------------------------*/
#ifndef __RUN_H
#define __RUN_H 

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC�ٷ�������
#include "Master_Protocol.h"

/* ȫ�ֺ궨�� -----------------------------------------------------------------*/

/* �ṹ������ -----------------------------------------------------------------*/ 
/* ���ֿ��ؽṹ�� ------------------------------*/
typedef struct  __Switch
{
   unsigned char RS485_Reply;//����һ������
   unsigned char Show_Send_Receive;//��ʾ���ͻ�������� 0������  1������
   unsigned char a_Relay[MAGNET_NUMBER];//�̵���
   unsigned char a_Magnet[MAGNET_NUMBER];//���
   unsigned char a_Demagnet[MAGNET_NUMBER];//�˴�
   unsigned char Inquiry;//��ѯ
   unsigned char Receive;//������һ֡���ݣ�1 δ�����꣺0
   
}__Switch_Def;

/* ������Ϣ�ṹ�� ------------------------------*/
typedef struct  __Msg
{
   unsigned char Order;           //ָ��
   unsigned char a_Parameter[4]; //�������� :���ĸ�
   unsigned char Hardware_Type;  //Ӳ�����ͣ��ֱ������壬��ʾ��
   unsigned char new_info;        //��Ϣ���������  0�Ѵ���ľ����ݣ�1������
   unsigned char Magnet_Strength; //���ǿ��
   unsigned char Demagnet_Strength;//�˴�ǿ��
   
}__Msg_Def;

/* �������ݽṹ�� ------------------------------*/
typedef struct __ComData
{
    uint  Current;        //����ֵ
    uchar TiltingX;       //X����б�Ƕ� 
    uchar TiltingY;       //Y����б�Ƕ� 
    uint  Weight;         //����
    uchar Temp;           //�¶�ֵ 
    uchar Magnet_Flag;   //��ű�־
    uchar Demagnet_Flag; //�˴ű�־
    
}__ComDataDef;

/* ö������ -----------------------------------------------------------------*/ 
enum __Hardware_Type
{
    Type_HANDLE = 0, //�ֱ�
    Type_MASTER,     //����
    Type_SENSOR        
};

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 
extern __Switch_Def gs_Switch;    //���ֿ��ؽṹ��
extern __Msg_Def gsa_Msg[10];     //������Ϣ
extern __ComDataDef gs_ComData;   //����ϵͳ�Ĺ�����������

/* ȫ�ֺ������� ---------------------------------------------------------------*/  
void Manage_Incident();
void ManageMessage();
void ShowResult();

#endif
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

