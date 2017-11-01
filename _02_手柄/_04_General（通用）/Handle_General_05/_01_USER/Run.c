/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : Run.c
* @Description : None
* @Date         : 2015/12/9
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : ���̵���Ҫ����Դ�ļ�
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "Run.h"                        
#include <pic18f67k22.h>                //PIC�ٷ�������
#include "Config_18F67K22.h"           //����PICоƬ   
#include "My_Delay.h"                   //��ʱ
#include "GPIO.h"                       //GPIO�ڵ�����
#include "My_Types.h"                   //�Զ����ϰ��д������
#include "Key.h"                        //��д����
#include "TM1640.h"                     //LED��ʾ
#include "My_ADC.h"                     //ADC
#include "My_Timer.h"                   //��ʱ��
#include "My_USART.h"                   //���� 

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/
unsigned char ReceiveBuff[RS485_DATA_LENTH]; //�������ݵ��û�������

/* ˽�У���̬���������� --------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/
__Switch_Def gs_Switch = {0};               //���ֿ��ؽṹ��
__Msg_Def gsa_Msg[DEVICE_NUMBER] = {0};     //������Ϣ
__ComDataDef gs_ComData;                    //����ϵͳ�Ĺ�����������

/* ȫ�ֺ�����д ---------------------------------------------------------------*/


/**----------------------------------------------------------------------------
* @Function_Name : ManageMessage()     
* @Description   : ������
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/9 
* @Explain       : None
------------------------------------------------------------------------------*/
void ManageMessage()
{
    Key_ManageMessage();  //���ذ�����Ϣ����  
    RS485_ManageMessage(ga_RS485_ReceiveBuff,RS485_DATA_LENTH);  //RS485��Ϣת�洦��
    RS485_AnalysisData();  //��Ϣ����    
    
}
    
    
/**----------------------------------------------------------------------------
* @Function_Name : Running()     
* @Description   : ���к���
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Run()
{
  /* ADC6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/ 
  if( gs_Switch.ADC6 )  GetADC6(); //ADC6�ɼ�

  /* �������ݴ���  =-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-*/ 
   if ( gs_Switch.Usart_OneDate ) 
   {
        gs_Switch.Usart_OneDate = 0;                                                             
        RS485_SendDate(ga_RS485_SendBuff,RS485_DATA_LENTH);
   }
   
     
}


/**----------------------------------------------------------------------------
* @Function_Name : ShowResult()     
* @Description   : ��ʾ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void ShowResult()
{
    if( gs_Switch.Show_Send_Receive )       
    {
        TM1640_Show_integer( ga_RS485_SendBuff[g_RS485_Byte] + (g_RS485_Byte * 1000) ); 
        LED1_ON();    
    }
    
    else
    {
        TM1640_Show_integer( ga_RS485_ReceiveBuff[g_RS485_Byte] + (g_RS485_Byte * 1000) ); 
        LED1_OFF();                  
    }
    
  
}


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

