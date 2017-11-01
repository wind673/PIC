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
            
            /* �жϷ��ͷ�Ӳ������ --------------------------*/
            from_dress = DataBuff[date_lenth - 3];
            if( from_dress < 0x10 )  gsa_Msg[from_dress].Hardware_Type = Type_HANDLE;      //�ֱ�:0x00~0x0f
            else if( from_dress < 0x20 )  gsa_Msg[from_dress].Hardware_Type = Type_MASTER; //����:0x10~0x1f
            else if( from_dress < 0x30 )  gsa_Msg[from_dress].Hardware_Type = Type_SENSOR; //������:0x20~0x2f
                
            /* ת������ -----------------------------------*/                       
            gsa_Msg[from_dress].Order = DataBuff[RS485_ORDER_BYTE]; //ת��ָ��                 
            gsa_Msg[from_dress].a_Parameter[0] =  DataBuff[RS485_DATA_BYTE0]; //ת�����       
            gsa_Msg[from_dress].a_Parameter[1] =  DataBuff[RS485_DATA_BYTE1];                 
            gsa_Msg[from_dress].a_Parameter[2] =  DataBuff[RS485_DATA_BYTE2];                 
            gsa_Msg[from_dress].a_Parameter[3] =  DataBuff[RS485_DATA_BYTE3];                     
                
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
   
    for( _Addr = Address_All; _Addr < DEVICE_NUMBER; _Addr++ ) //��ַ�����ѯ
    if( gsa_Msg[_Addr].new_info == 1 ) //�Ƿ�Ϊ������
    {
        //װ�ص�ַ
        _PreData[RS485_LOCAL_ADRESS_BYTE] = Local_Address;             
        _PreData[RS485_DEST_ADRESS_BYTE] = _Addr;             
         
        /* �򱾻����в��� =============================================================*/
        /* ����ָ�� ---------------------------------*/    
        if( gsa_Msg[_Addr].Order == Cmd_Reset ) 
        {
            gs_ComData.Current = Default_Current;   
            gs_ComData.Temp = Default_Temp;         
            gs_ComData.TiltingX = Default_TiltingX;     
            gs_ComData.TiltingY = Default_TiltingY;     
            gs_ComData.Weight = Default_Weight;         
        }
        
        /* ���ָ�� ---------------------------------*/                                  
        else if( gsa_Msg[_Addr].Order == Cmd_Magnet ) 
        { 
            for(temp = 0; temp < MAGNET_CH_NUMBER ; temp++ )
            gs_Switch.a_Magnet[temp] = gsa_Msg[_Addr].a_Parameter[0] & ( 0x01 << temp ); //����ͨ�����Ŀ���
 
            /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       
             * �˴�д��ź���������
             * 
             *         
             */
            
        }
        
        /* �˴�ָ�� ---------------------------------*/   
        else if( gsa_Msg[_Addr].Order == Cmd_Demagnet ) 
        {
           for(temp = 0; temp < MAGNET_CH_NUMBER ; temp++ )
            gs_Switch.a_Demagnet[temp] = gsa_Msg[_Addr].a_Parameter[0] & ( 0x01 << temp ); //����ͨ�����Ŀ���
           /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@       
             * �˴�д�˴ź���������
             * 
             *         
             */
           
        }
        
        /* �򱾻�д������ =============================================================*/
        /* �򱾻�д����� ---------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Write_Current ) 
        {
            gs_ComData.Current = gsa_Msg[_Addr].a_Parameter[0];      //���ݵ�λ  
            gs_ComData.Current += gsa_Msg[_Addr].a_Parameter[1]*256; //���ݸ�λ 
        }                                                                                                     
           
        /* �򱾻�д����б�� --------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Write_Tilting ) 
        {
            gs_ComData.TiltingX = gsa_Msg[_Addr].a_Parameter[0];        
            gs_ComData.TiltingY = gsa_Msg[_Addr].a_Parameter[1];           
        }
        
        /* �򱾻�д������ -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Write_Weight ) 
        {
            gs_ComData.Weight = gsa_Msg[_Addr].a_Parameter[0];
            gs_ComData.Weight += gsa_Msg[_Addr].a_Parameter[1]*256; 
        }
        
        /* �򱾻�д���¶� -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Write_Temp ) 
        {
            gs_ComData.Temp = gsa_Msg[_Addr].a_Parameter[0];
        }
        
        /* �򱾻���ȡ���� =============================================================*/
        /* �򱾻���ȡ���� -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Read_Current ) 
        {
            ga_RS485_SendBuff[RS485_DATA_BYTE0] = gs_ComData.Current%256; //װ��д��������ݵ�λ
            ga_RS485_SendBuff[RS485_DATA_BYTE1] = gs_ComData.Current/256; //װ��д��������ݸ�λ
            ga_RS485_SendBuff[RS485_DATA_BYTE2] = RS485_VACANT;            //װ�ؿ���ֵ
            ga_RS485_SendBuff[RS485_DATA_BYTE3] = RS485_VACANT;     
            
            ga_RS485_SendBuff[RS485_ORDER_BYTE] = Cmd_Write_Current;       //װ��д���������     
            
            gs_Switch.RS485_Reply = 1; //�������ݣ�д��־λ��
            
        }
        
        /* �򱾻���ȡ��б�� -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Read_Tilting ) 
        {
            ga_RS485_SendBuff[RS485_ORDER_BYTE] = Cmd_Write_Tilting;       //װ��д������    
            ga_RS485_SendBuff[RS485_DATA_BYTE0] = gs_ComData.TiltingX;    //װ��д����б��X��    
            ga_RS485_SendBuff[RS485_DATA_BYTE1] = gs_ComData.TiltingY;    //װ��д����б��X��        
            ga_RS485_SendBuff[RS485_DATA_BYTE2] = RS485_VACANT;            
            ga_RS485_SendBuff[RS485_DATA_BYTE3] = RS485_VACANT;     
            gs_Switch.RS485_Reply = 1;   //��������
        }
        
         /* �򱾻���ȡ���� -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Read_Weight ) 
        {
            ga_RS485_SendBuff[RS485_ORDER_BYTE] = Cmd_Write_Weight;         //װ��д���������            
            ga_RS485_SendBuff[RS485_DATA_BYTE0] = gs_ComData.Weight % 256; //װ��д���������ݵ�λ     
            ga_RS485_SendBuff[RS485_DATA_BYTE1] = gs_ComData.Weight / 256; //װ��д���������ݸ�λ     
            ga_RS485_SendBuff[RS485_DATA_BYTE2] = RS485_VACANT;             //װ�ؿ���ֵ  
            ga_RS485_SendBuff[RS485_DATA_BYTE3] = RS485_VACANT;     
            gs_Switch.RS485_Reply = 1;         //��������
        }
        
         /* �򱾻���ȡ�¶� -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Read_Temp ) 
        {
            ga_RS485_SendBuff[RS485_ORDER_BYTE] = Cmd_Write_Temp;          //װ��д���¶�����
            ga_RS485_SendBuff[RS485_DATA_BYTE0] = gs_ComData.Temp;        //װ��д���¶�����
            ga_RS485_SendBuff[RS485_DATA_BYTE1] = RS485_VACANT;            //װ�ؿ���ֵ
            ga_RS485_SendBuff[RS485_DATA_BYTE2] = RS485_VACANT;              
            ga_RS485_SendBuff[RS485_DATA_BYTE3] = RS485_VACANT;                  
                                                                
            gs_Switch.RS485_Reply = 1;      //��������
        }
                     
    gsa_Msg[_Addr].new_info = 0; //�����ݴ������    
    }  
}
    
           
   
    
        
        
/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/





