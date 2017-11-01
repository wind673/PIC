/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : My_USART.c
* @Description : ����ͨѶԴ�ļ�
* @Date         : 2015/10/29
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "My_USART.h"
#include "usart.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/
unsigned int USART2_TendBuff = 0;
unsigned int USART2_ReceiveBuff = 0;
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
    Open2USART( USART_TX_INT_OFF  &
                 USART_RX_INT_ON   &
                 USART_ASYNCH_MODE &
                 USART_EIGHT_BIT   &
                 USART_CONT_RX     &
                 USART_BRGH_LOW    
                ,
                 12 //������Ϊ��9600
                );
    
    TRISGbits.TRISG1 = 1;     //RG1:RX2 ����Ϊ����             
    TRISGbits.TRISG2 = 0;     //RG2:TX2 ����Ϊ���
    TRISGbits.TRISG3 = 0;     //RG3:RS485CON ����Ϊ���
    RS485_OFF();               //RS485��ʼ��Ϊ����״̬
    ANCON2 &= 0XF1;            //�ر�GPIO1,2��3��ģ������
}


/**----------------------------------------------------------------------------
* @Function_Name : RS485_Send_Date(unsigned char *date_dress, unsigned char date_lenth)
* @Description   : ���ʹ���2������
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
void RS485_Send_Date(unsigned char *date_dress, unsigned char date_lenth)
{
    while( date_lenth -- )
    {
        while( Busy2USART()); //�ȴ�Usart2����  
        RS485_ON();           //��RS485             
        TXREG2 = USART2_TendBuff;   
        while( Busy2USART()); //�ȴ�Usart2�������     
        RS485_OFF();           //�ر�RS485
    }
    
    
}


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/





