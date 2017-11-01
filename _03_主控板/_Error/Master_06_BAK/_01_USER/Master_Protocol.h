/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : Master_Protocol.h
* @Description : �ֱ�ͨѶЭ��ͷ�ļ�
* @Date        : 2015/12/20
* @By          : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* ��ֹ�ص��� -----------------------------------------------------------------*/
#ifndef __MASTER_PROTOCOL_H
#define __MASTER_PROTOCOL_H 

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "My_Types.h"
#include <pic18f67k22.h>                //PIC�ٷ�������

/* ȫ�ֺ궨�� -----------------------------------------------------------------*/
/* ���� ---------------------------------*/
#define DEVICE_NUMBER 10       //�豸����
#define MAGNET_NUMBER 3        //��ͨ����
#define INQUIRY_INTERVAL 50    //��ѯʱ����
#define MAGNET_CH_NUMBER 8     //��ͨ����

/* ����λ ---------------------------------*/
#define RS485_ORDER_BYTE 6     //ָ��λ
#define RS485_DATA_BYTE0 2     //����λ
#define RS485_DATA_BYTE1 3
#define RS485_DATA_BYTE2 4
#define RS485_DATA_BYTE3 5
#define RS485_LOCAL_ADRESS_BYTE  7  //���ص�ַλ
#define RS485_DEST_ADRESS_BYTE   8  //Ŀ���ַλ

/* ������ ---------------------------------*/
#define CRC_CODE 0xffff         //CRCУ����
#define RS485_START 0xff        //��ʼ��
#define RS485_VACANT 0xaa       //�����������

/* ȫ��ö�ٶ��� -----------------------------------------------------------------*/
/* ��ַ ---------------------------------------------------*/
enum __Address
{
   
    Address_Master = 0x00,       //���ذ�
    Address_Sensor ,             //������  
    Address_SMPDP ,              //��ʾ��    
    Address_Handle_A = 0x03,     //A���ֱ�   
    Address_Handle_B ,           //B���ֱ�
    Address_Handle_C ,           //C���ֱ�
    Address_Handle_D ,           //D���ֱ�
    
    RS485_DATA_LENTH,            //��������
    Address_All,                 //ȫ�ֹ㲥        
};

/* ����ָ�� ------------------------------------------------*/
enum __Cmd   
{
    /* ����ָ�� --------------------------*/
    Cmd_Reset = 0x00,            //�����������ݵ�Ĭ��״̬  
    Cmd_Magnet ,                 //���     
    Cmd_Demagnet ,               //�˴�      
    Cmd_Inquiry ,                //��ѯ
    
    /* д��ָ�� --------------------------*/
    Cmd_Write_Current ,          //д���������
    Cmd_Write_Tilting ,          //д����б����    
    Cmd_Write_Weight ,           //д����������  
    Cmd_Write_Temp ,             //д���¶Ȳ���  
    
    /* ��ȡָ�� --------------------------*/    
    Cmd_Read_Current ,           //��ȡ��������     
    Cmd_Read_Tilting ,           //��ȡ��б����    
    Cmd_Read_Weight ,            //��ȡ��������  
    Cmd_Read_Temp ,              //��ȡ�¶Ȳ���   
    
    /* ״ָ̬�� --------------------------*/  
    Cmd_State_Success ,          //�ɹ�״̬�����ڷ��ز��������  
    Cmd_State_Failure ,          //�ɹ�״̬�����ڷ��ز��������  
    Cmd_State_Warning ,          //�ɹ�״̬�����ڷ��ز��������  
    
    
};    

/* Ĭ�ϲ��� ------------------------------------------------*/                              
enum __Default
{
    Default_Current = 0,       //����Ĭ��ֵ
    Default_TiltingX = 0,      //X����б�Ƕ�Ĭ��ֵ 
    Default_TiltingY = 0,      //Y����б�Ƕ�Ĭ��ֵ 
    Default_Weight = 0,        //����Ĭ��ֵ     
    Default_Temp = 0,          //�¶�ֵĬ��ֵ 
    
}; 

/* �ṹ������ -----------------------------------------------------------------*/ 

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 
extern unsigned char ga_RS485_SendBuff[RS485_DATA_LENTH];    //RS485�������ݻ�����
extern unsigned char ga_RS485_ReceiveBuff[RS485_DATA_LENTH]; //RS485�������ݻ�����
extern unsigned char g_RS485_Receive_Flag;                 //RS485������ɱ�־
extern unsigned char g_RS485_Byte;                         //RS485�ֽ�λ
extern unsigned char g_Inquiry_Flag;                       //��ѯ��־λ

/* ȫ�ֺ������� ---------------------------------------------------------------*/  
unsigned char  RS485_RecogniseMessage( unsigned char DataBuff[] ,unsigned char date_lenth );
void RS485_AnalysisData(void);
void VerifyCRC(unsigned char *DataBuff,unsigned char date_lenth);
void RS485_Inquiry(void);

#endif
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

