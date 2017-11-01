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
void My_USART_Init()
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
    RS485_RX();                //RS485��ʼ��Ϊ����״̬
    RCEN2 = 1;
}

void Write2USART(char data)
{
  if(TXSTA2bits.TX9)  // 9-bit mode?
  {
    TXSTA2bits.TX9D = 0;       // Set the TX9D bit according to the
    if(USART2_Status.TX_NINE)  // USART2 Tx 9th bit in status reg
      TXSTA2bits.TX9D = 1;
  }
  
  TXREG2 = data;      // Write the data byte to the USART2
}


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/





