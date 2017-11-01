/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : Master_Protocol.c
* @Description : �ֱ�ͨѶЭ��Դ�ļ�
* @Date         : 2015/12/20
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : �ӻ���ֻ��Ҫ��������������£�����Ҫ������������
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/       
#include <pic18f67k22.h>
#include "Master_Protocol.h"
#include "usart.h"
#include <math.h>
#include "Run.h"
#include "Config_18F67K22.h"
#include "My_USART.h"
#include "Run.h"     

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/
  
/* ˽�У���̬���������� --------------------------------------------------------*/
static void Cmd_Inquiry_Fun(uchar _Addr);

/* ȫ�ֱ������� ---------------------------------------------------------------*/
unsigned char ga_RS485_SendBuff[RS485_DATA_LENTH] = {0};      //RS485�������ݻ�����         
unsigned char ga_RS485_ReceiveBuff[RS485_DATA_LENTH] = {0};   //RS485�������ݻ����� 
unsigned char g_RS485_Byte = 0;                               //RS485�ֽ�λ             
unsigned char g_RS485_Receive_Flag = 0; 

/* ˽�к�����д ---------------------------------------------------------------*/

/**---------------------------------------------------------------------------- 
 * @Function_Name : Cmd_Inquiry_Fun()
 * @Description   : ��ѯ����
 * @Parameter     : void
 * @Return        �� void
 * @Programer     : WindRises��л���죩
 * @Data          : 2015/12/19
 * @Explain       : None
------------------------------------------------------------------------------*/
static void Cmd_Inquiry_Fun(uchar _Addr)
{
    uchar _PreData[RS485_DATA_LENTH]; //׼�����͵�����
    /* װ�ص�ַ -----------------------------------*/
    _PreData[RS485_LOCAL_ADRESS_BYTE] = Local_Address;                              
    _PreData[RS485_DEST_ADRESS_BYTE] = _Addr;                                 
     
    /* װ������ -----------------------------------*/
    _PreData[RS485_DATA_BYTE0] = RS485_VACANT; //װ��д��������ݵ�λ
    _PreData[RS485_DATA_BYTE1] = RS485_VACANT; //װ��д��������ݸ�λ
    _PreData[RS485_DATA_BYTE2] = RS485_VACANT; //װ�ؿ���ֵ
    _PreData[RS485_DATA_BYTE3] = RS485_VACANT;     
    
    /* װ������ -----------------------------------*/
    _PreData[RS485_ORDER_BYTE] = Cmd_Inquiry;       //װ�ز�ѯ����   
    
    RS485_SendDate(_PreData,RS485_DATA_LENTH);    //��������
        
}

/* ȫ�ֺ�����д ---------------------------------------------------------------*/

/**---------------------------------------------------------------------------- 
 * @Function_Name : RS485_Inquiry()
 * @Description   : ѭ����ѯ����
 * @Parameter     : void
 * @Return        �� void
 * @Programer     : WindRises��л���죩
 * @Data          : 2015/12/19
 * @Explain       : ��������ѭ����ѯ
------------------------------------------------------------------------------*/
void RS485_Inquiry(void)
{   
    static unsigned char  _NowAddr = Address_Handle_A;
    uchar _PreData[RS485_DATA_LENTH]; //׼�����͵�����
   
    if( gs_Switch.Inquiry == 1 )  //Timer1��ʱ���� Inquiry
    { //��ʱ��ѯ
      
        Cmd_Inquiry_Fun(_NowAddr);   //���Ͳ�ѯָ��                 
        _NowAddr ++;  
        if( _NowAddr == RS485_DATA_LENTH ) _NowAddr = Address_Handle_A;  //ѭ����ѯ
        
        gs_Switch.Inquiry = 0;   //��ѯ���
    }   
    
}

    
/**----------------------------------------------------------------------------
 * @Function_Name : RS485_RecogniseMessage( )
 * @Description   : RS485��Ϣʶ��
 * @Parameter     : DataBuff[]��RS485�����յ�һ֡���� 
 *                    date_lenth��һ֡���ݵĳ���
 * @Return        : char
 * @Programer     : WindRises��л���죩
 * @Data          : 2015/12/13
 * @Explain       : ���ճɹ�����1  ���򷵻�0
------------------------------------------------------------------------------*/
unsigned char  RS485_RecogniseMessage( unsigned char DataBuff[] ,unsigned char date_lenth )
{
     unsigned char CRC_H,CRC_L,from_dress;
     if( gs_Switch.Receive == 1 )  //ֻ�н�����һ�����ݲŻ��������
     {
            /* �ж���ʼ�� ---------------------------------*/  
            if( DataBuff [date_lenth-1] != 0xaa)  {  gs_Switch.Receive = 0; return 1;}  //��ʼ�����      

            /* �ж�CRCУ���� ------------------------------*/        
            CRC_H = DataBuff[1];  //ת��CRCУ����  
            CRC_L = DataBuff[0];       
            VerifyCRC(DataBuff,RS485_DATA_LENTH);  
            if( DataBuff[1] != CRC_H ) {  gs_Switch.Receive = 0; return 2 ;}   //CRCУ�����
            if( DataBuff[0] != CRC_L ) {  gs_Switch.Receive = 0; return 2 ;} 
            
            /* �жϵ�ַ ----------------------------------*/
            if( ( DataBuff[date_lenth - 2] != Local_Address )  && ( DataBuff[date_lenth - 2] != Address_All) ) {  gs_Switch.Receive = 0; return 3;}//�Ǳ�����ַ
            
          
            
            /* ������� -----------------------------------*/
            gsa_Msg[from_dress].new_info = 1; //����ת�����,Ϊ������
            gs_Switch.Receive = 0;   
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
 void VerifyCRC(unsigned char *DataBuff,unsigned char date_lenth)
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


/**---------------------------------------------------------------------------- 
 * @Function_Name : RS485_AnalysisData()
 * @Description   : ���ݷ�������
 * @Parameter     : void
 * @Return        �� void
 * @Programer     : WindRises��л���죩
 * @Data          : 2015/12/19
 * @Explain       : None
------------------------------------------------------------------------------*/
void RS485_AnalysisData(void)
{
   uchar _Addr,temp;
   uchar _PreData[RS485_DATA_LENTH];
   
 
                     
    gsa_Msg[_Addr].new_info = 0; //�����ݴ������    
    
}
    
           
   
    
        
        
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/





