/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : My_USART.c
* @Description : ����ͨѶԴ�ļ�
* @Date         : 2015/10/29
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : ���ڹ���ʵ��Դ�ļ�
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "My_USART.h"
#include "usart.h"
#include <math.h>
#include "Run.h"
#include "Config_18F67K22.h"
#include "Relay.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/

/* ȫ�ֺ�����д ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : My_USART_Init()     
* @Description   : ����ͨ�ų�ʼ��
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
void RS485_Init()
{
    Open1USART( USART_TX_INT_OFF  &
                 USART_RX_INT_ON   &
                 USART_ASYNCH_MODE &
                 USART_EIGHT_BIT   &
                 USART_CONT_RX     &
                 USART_BRGH_LOW    
                ,
                 12 //������Ϊ��9600
                );
    
    TRISC7 = 1;     //RX1 ����Ϊ����             
    TRISC6 = 0;     //TX1 ����Ϊ���
    TRISC0 = 0;     //RS485CON ����Ϊ���
    RS485_OFF();    //RS485��ʼ��Ϊ����״̬
    
}



/**---------------------------------------------------------------------------- 
 * @Function_Name : RS485_SendDate(unsigned char *date_dress, unsigned char date_lenth)
 * @Description   : ���ʹ���1������
 * @Parameter     : void
 * @Return        : void
 * @Programer     : WindRises��л���죩
 * @Data          : 2015/10/29
 * @Explain       : �ȷ���λ�ٷ���λ
------------------------------------------------------------------------------*/
void RS485_SendDate(unsigned char *date_dress, unsigned char date_lenth)
{
    /* װ����ʼ�� ------------------------------------*/              
    date_dress[--date_lenth] = RS485_START;   
    
    /* װ��CRCУ���� ---------------------------------*/                       
    VerifyCRC(date_dress,date_lenth);  
    
    /* ׼������ --------------------------------------*/        
    while( Busy1USART() );      //�ȴ�Usart1�������    
    RS485_ON();    //��RS485 
    
    /* ������ʼ�� -----------------------------------*/
    TXREG1 = date_dress[date_lenth];           
    while( Busy1USART() );      //�ȴ�Usart1�������  
    
    /* ��������λ -----------------------------------*/
    while( date_lenth --) 
    {
        if(date_dress[date_lenth] == RS485_START )  date_dress[date_lenth]--;    //��ֹ������ʼ�룬������������
        TXREG1 = date_dress[date_lenth];   
        while( Busy1USART()); //�ȴ�Usart1�������     
    }
    
    RS485_OFF(); //�ر�RS485
    gs_Switch.RS485_Reply = 0; //�������
}

        
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/





