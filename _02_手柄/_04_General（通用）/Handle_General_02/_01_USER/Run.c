/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : Run.c
* @Description : None
* @Date         : 2015/12/9
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
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
#include "usart.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/
unsigned char ReceiveBuff[RS485DATA_LENTH]; //�������ݵ��û�������

/* ˽�У���̬���������� --------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/
__Switch_Def Handle_Switch = {0,0,0,0}; //���ֿ��ؽṹ��
__Msg_Def Handle_Msg[10] = {0,{0}};     //������Ϣ
        

/* ȫ�ֺ�����д ---------------------------------------------------------------*/


/**----------------------------------------------------------------------------
* @Function_Name : Manage_Message()     
* @Description   : ������
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Message_Manage()
{
    Key_Message_Manage();//���ذ�����Ϣ����
    RS485_Message_Manage(RS485_ReceiveBuff,RS485DATA_LENTH);//RS485��Ϣ����
    
    
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
  if( Handle_Switch.ADC6 )  Get_ADC6(); //ADC6�ɼ�

  /* �������ݴ���  =-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-*/ 
   if ( Handle_Switch.Usart_OneDate ) 
   {
        Handle_Switch.Usart_OneDate = 0;      
        RS485_Send_Date(RS485_SendBuff,RS485DATA_LENTH);
        
   }
  
  
 
     
  
}


/**----------------------------------------------------------------------------
* @Function_Name : Result_Show()     
* @Description   : ��ʾ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Result_Show()
{
    if( Handle_Switch.Show_Send_Receive )       
    {
        TM1640_Show_integer( RS485_SendBuff[RS485_Num] + (RS485_Num * 1000) ); 
        LED1_ON();   
    }
    
    else
    {
        TM1640_Show_integer( RS485_ReceiveBuff[RS485_Num] + (RS485_Num * 1000) ); 
        LED1_OFF();                  
    }
    

}


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

