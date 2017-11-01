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
#include "Config_18F167K22.h"           //����PICоƬ   
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

/* ˽�У���̬���������� --------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/


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
void Manage_Message()
{
    if (Key_FSM_Read(4) == KEY_short )  USART2_TendBuff ++;
    if (Key_FSM_Read(1) == KEY_short )  Handle_01_Switch.Usart_OneDate = 1; 
    if (Key_FSM_Read(2) == KEY_short )  USART2_TendBuff --;
        
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
  /*=-=-=-=-=-=-=-=-=-=-=-=- ADC6 =-=-=-=-=-=-=-=-=-=-=-*/ 
  if( Handle_01_Switch.ADC6 )  Get_ADC6(); //ADC6�ɼ�

  /*=-=-=-=-=-=-=-=-=-=-=-=- �������ݴ���  =-=-=-=-=-=-=-=-=-=-=-*/ 
   if ( Handle_01_Switch.Usart_OneDate ) 
   {
        Handle_01_Switch.Usart_OneDate = 0;      
        
        while( Busy2USART()); //�ȴ�Usart2����  
        RS485_ON();           //��RS485             
        TXREG2 = USART2_TendBuff;   
        while( Busy2USART()); //�ȴ�Usart2�������     
        RS485_OFF();           //�ر�RS485
        
   }
   
     
   
}



/**----------------------------------------------------------------------------
* @Function_Name : Show_Result()     
* @Description   : ��ʾ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Show_Result()
{
//    TM1640_Show_Decimal( ADC6_Buff ); //��ʾADC�ɼ�������        
    
    TM1640_Show_integer( USART2_TendBuff );          
//    TM1640_Show_integer( USART2_ReceiveBuff ); 
}


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

