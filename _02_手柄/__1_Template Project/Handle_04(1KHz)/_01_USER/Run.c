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
#include "My_ADC.h"
#include "My_Timer.h"                     //ADC


/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/


/* ȫ�ֺ�����д ---------------------------------------------------------------*/

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
  static unsigned char _overturn_LED = 0;
  
  /*=-=-=-=-=-=-=-=-=-=-=-=- ADC6 =-=-=-=-=-=-=-=-=-=-=-*/ 
  if( Handle_01_Switch.ADC6 )  Get_ADC6(); //ADC6�ɼ�

  /*=-=-=-=-=-=-=-=-=-=-=-=- ָʾ����˸  =-=-=-=-=-=-=-=-=-=-=-*/        
        if( Timer_Cyc%1000 == 0 )  //����ָʾ����˸
        {
            _overturn_LED = ~_overturn_LED;
            if(_overturn_LED)  LED3_ON; 
            else           LED3_OFF;
        }
   
}

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
    if (Key_FSM_Read(1) == KEY_short )  Handle_01_Switch.ADC6 = ~Handle_01_Switch.ADC6;
    if (Key_FSM_Read(4) == KEY_short )  Handle_01_Switch._1Khz = ~Handle_01_Switch._1Khz;   
    
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
      TM1640_Show_Decimal( ADC6_Buff ); //��ʾADC�ɼ�������
      
      
}


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

