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
#include <math.h>

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/
static static void CRC_Verify(unsigned char *DataBuff);

/* ȫ�ֱ������� ---------------------------------------------------------------*/
unsigned char RS485_SendBuff[RS485DATA_LENTH] = {0};      //RS485�������ݻ�����
unsigned char RS485_ReceiveBuff[RS485DATA_LENTH] = {0};   //RS485�������ݻ�����
unsigned char RS485_Receive_Flag = 0;                     //RS485������ɱ�־
unsigned char RS485_Num = 0;                       //RS485�ֽ�λ


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
* @Explain       : �ȷ���λ�ٷ���λ
------------------------------------------------------------------------------*/
void RS485_Send_Date(unsigned char *date_dress, unsigned char date_lenth)
{

    /* װ����ʼ�� ------------------------------------*/              
    date_dress[date_lenth-1] = RS485_START;   
    
    /* װ��CRCУ���� ---------------------------------*/                       
    CRC_Verify(date_dress);  
    
    /* ׼������ --------------------------------------*/        
    while( Busy2USART() );      //�ȴ�Usart2�������    
    RS485_ON();    //��RS485 
    
    /* ��������λ -----------------------------------*/
    while( date_lenth --) 
    {
        TXREG2 = date_dress[date_lenth];   
        while( Busy2USART()); //�ȴ�Usart2�������     
    }
    
    RS485_OFF(); //�ر�RS485
}

/**----------------------------------------------------------------------------
* @Function_Name : RS485_Receive_Date( unsigned char DataBuff[] )
* @Description   : RS485��������
* @Parameter     : void
* @Return        : char
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/13
* @Explain       : ���ճɹ�����1  ���򷵻�0
------------------------------------------------------------------------------*/
void RS485_Receive_Date( unsigned char DataBuff[] )
{


}


/**----------------------------------------------------------------------------
* @Function_Name : CRC_Verify(unsigned char *DataBuff)
* @Description   : CRCУ��������
* @Parameter     : unsigned char *DataBuff 
* @Return        :  void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/13
* @Explain       : ת��CRCֵ(2byte)
------------------------------------------------------------------------------*/
static void CRC_Verify(unsigned char *DataBuff)
{
    unsigned long int CRC_Value = 0;
    uchar CRC_Byte;
    
    for(CRC_Byte = 2;CRC_Byte < RS485DATA_LENTH ;CRC_Byte++)
    CRC_Value  =  ( CRC_Value + DataBuff[CRC_Byte]*CRC_Byte ) % CRC_CODE;           
    
    DataBuff[1] = CRC_Value/0xff;  
    DataBuff[0] = CRC_Value%0xff; //���ݲ���
    
    if( DataBuff[1] == RS485_START ) DataBuff[1] --;//������� ��ʼ��
    if( DataBuff[0] == RS485_START ) DataBuff[0] --;
     
}

/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/





