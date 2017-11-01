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


/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/
static void VerifyCRC(unsigned char *DataBuff,unsigned char date_lenth);

/* ȫ�ֱ������� ---------------------------------------------------------------*/
unsigned char ga_RS485_SendBuff[RS485DATA_LENTH] = {0};      //RS485�������ݻ�����
unsigned char ga_RS485_ReceiveBuff[RS485DATA_LENTH] = {0};   //RS485�������ݻ�����
unsigned char g_RS485_Receive_Flag = 0;                     //RS485������ɱ�־
unsigned char g_RS485_Byte = 0;                             //RS485�ֽ�λ


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
 * @Description   : ���ʹ���2������
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
    VerifyCRC(date_dress,RS485DATA_LENTH);  
    
    /* ׼������ --------------------------------------*/        
    while( Busy1USART() );      //�ȴ�Usart2�������    
    RS485_ON();    //��RS485 
    
    /* ������ʼ�� -----------------------------------*/
    TXREG1 = date_dress[date_lenth];           
    while( Busy1USART() );      //�ȴ�Usart2�������  
    
    /* ��������λ -----------------------------------*/
    while( date_lenth --) 
    {
        if(date_dress[date_lenth] == RS485_START )  date_dress[date_lenth]--;//��ֹ������ʼ�룬������������
        TXREG1 = date_dress[date_lenth];   
        while( Busy1USART()); //�ȴ�Usart2�������     
    }
    
    RS485_OFF(); //�ر�RS485
}

/**----------------------------------------------------------------------------
 * @Function_Name : RS485_ManageMessage( )
 * @Description   : RS485��Ϣ��������
 * @Parameter     : DataBuff[]��RS485�����յ�һ֡���� 
 *                    date_lenth��һ֡���ݵĳ���
 * @Return        : char
 * @Programer     : WindRises��л���죩
 * @Data          : 2015/12/13
 * @Explain       : ���ճɹ�����1  ���򷵻�0
------------------------------------------------------------------------------*/
unsigned char  RS485_ManageMessage( unsigned char DataBuff[] ,unsigned char date_lenth )
{
     unsigned char CRC_H,CRC_L,from_dress;
     if( g_RS485_Receive_Flag == 1 )
     {
     
            /* �ж���ʼ�� ---------------------------------*/  
            if( DataBuff [date_lenth-1] != 0xaa)  { g_RS485_Receive_Flag = 0; return 1;}  //��ʼ�����      

            /* �ж�CRCУ���� ------------------------------*/        
            CRC_H = DataBuff[1];  //ת��CRCУ����
            CRC_L = DataBuff[0];
            VerifyCRC(DataBuff,RS485DATA_LENTH);  
            if( DataBuff[1] != CRC_H ) { g_RS485_Receive_Flag = 0; return 2 ;} //CRCУ�����
            if( DataBuff[0] != CRC_L ) { g_RS485_Receive_Flag = 0; return 2 ;} 

            /* �жϵ�ַ ----------------------------------*/
            if( ( DataBuff[date_lenth - 2] != Local_Address )  && ( DataBuff[date_lenth - 2] != All_Address) ) { g_RS485_Receive_Flag = 0; return 3;}//�Ǳ�����ַ

            /* �жϷ��ͷ�Ӳ������ --------------------------*/
            from_dress = DataBuff[date_lenth - 3];
            if( from_dress < 0x10 )  gsa_Handle_Msg[from_dress].Hardware_Type = Type_HANDLE; // �ֱ�:0x00~0x0f
            else if( from_dress < 0x20 )  gsa_Handle_Msg[from_dress].Hardware_Type = Type_MASTER; //����:0x10~0x1f
            else if( from_dress < 0x30 )  gsa_Handle_Msg[from_dress].Hardware_Type = Type_SENSOR; //������:0x20~0x2f

            /* ת������ -----------------------------------*/                       
            gsa_Handle_Msg[from_dress].Order = DataBuff[date_lenth - 4]; //ת��ָ��                 
            gsa_Handle_Msg[from_dress].a_Parameter[3] =  DataBuff[date_lenth -5]; //ת�����       
            gsa_Handle_Msg[from_dress].a_Parameter[2] =  DataBuff[date_lenth -6];                 
            gsa_Handle_Msg[from_dress].a_Parameter[1] =  DataBuff[date_lenth -7];                 
            gsa_Handle_Msg[from_dress].a_Parameter[0] =  DataBuff[date_lenth -8];                     

            /* ������� -----------------------------------*/
            gsa_Handle_Msg[from_dress].hand_info = 1;//���ݴ������
            g_RS485_Receive_Flag = 0;
     }
}


/**----------------------------------------------------------------------------
 * @Function_Name : CRC_Verify(unsigned char *DataBuff)
 * @Description   : CRCУ��������
 * @Parameter     : *DataBuff ����ҪCRCת��������
 *                    date_lenth��ת�������鳤��
 * @Return        :  void
 * @Programer     : WindRises��л���죩
 * @Data          : 2015/12/13
 * @Explain       : ת��CRCֵ(2byte)
------------------------------------------------------------------------------*/
static void VerifyCRC(unsigned char *DataBuff,unsigned char date_lenth)
{
    unsigned long int CRC_Value = 0;
    uchar CRC_Byte;
    
    for(CRC_Byte = 2; CRC_Byte < date_lenth ;CRC_Byte++)
    CRC_Value  =  ( CRC_Value + DataBuff[CRC_Byte]*CRC_Byte ) % CRC_CODE;           
    
    DataBuff[1] = CRC_Value/0xff;  
    DataBuff[0] = CRC_Value%0xff;   //���ݲ���
    
    if( DataBuff[1] == RS485_START ) DataBuff[1] --;  //������� ��ʼ��
    if( DataBuff[0] == RS485_START ) DataBuff[0] --;
      
}

/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/





