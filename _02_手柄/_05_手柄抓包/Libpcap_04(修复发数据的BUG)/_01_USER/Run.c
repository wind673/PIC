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
#include "usart.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/
unsigned char ReceiveBuff[RS485DATA_LENTH]; //�������ݵ��û�������
unsigned char g_Addr = 0; //�������ݵ��û�������
unsigned char Receive_Flag = 0;
/* ˽�У���̬���������� --------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/
__Switch_Def Handle_Switch = {0,0,0,0}; //���ֿ��ؽṹ��

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
    char i;
    Key_FSM_Read();
    /* ��ϰ���2,4 ---------------------------*/  
    if ( Local_Key_User.key_group == KEY_2_4 && Local_Key_User.key_group_state ==  KEY_short )  
    {  
        Handle_Switch.Show_Send_Receive = ~Handle_Switch.Show_Send_Receive ; 
        Key_FSM_Reset(); Receive_Flag =1;
    }
    
    /* ��ϰ���1,4 ---------------------------*/  
    if ( Local_Key_User.key_group == KEY_1_4 && Local_Key_User.key_group_state ==  KEY_short )  
    {  g_Addr++; Key_FSM_Reset();}
    
    /* ��ϰ���1,2 ---------------------------*/  
    if ( Local_Key_User.key_group == KEY_1_2 && Local_Key_User.key_group_state ==  KEY_short )  
    {  g_Addr--; Key_FSM_Reset();}
    
    /* ����5 -----------------------------*/  
    if (Local_Key_User.key_state[5-1] == KEY_short)  RS485_Num ++ ; //�жϰ���5�Ƿ�̰�
    if (Local_Key_User.key_state[5-1] == KEY_hold)  RS485_Num ++ ; //�жϰ���5�Ƿ񳤰�
    
    /* ����3 -----------------------------*/  
    if (Local_Key_User.key_state[3-1] == KEY_short)    RS485_Num -- ; //�жϰ���6�Ƿ�̰�
    if (Local_Key_User.key_state[3-1] == KEY_hold)    RS485_Num -- ; //�жϰ���6�Ƿ񳤰�
    
    if( RS485_Num > 250 ) RS485_Num = RS485DATA_LENTH - 1;
    else RS485_Num %= RS485DATA_LENTH;     //ʹ���Ȳ����� RS485DATA_LENTH
    
    /* ����4 ------------------------------*/   
    if (Local_Key_User.key_state[4-1] == KEY_short)  RS485_SendBuff[RS485_Num] ++ ; //�жϰ���4�Ƿ�̰�
    if (Local_Key_User.key_state[4-1] == KEY_hold)  RS485_SendBuff[RS485_Num] ++ ; //�жϰ���4�Ƿ񳤰�
    
    /* ����2 ------------------------------*/  
    if (Local_Key_User.key_state[2-1] == KEY_short)   RS485_SendBuff[RS485_Num] -- ; 
    if (Local_Key_User.key_state[2-1] == KEY_hold)    RS485_SendBuff[RS485_Num] -- ; 
    
    RS485_SendBuff[RS485_Num] %= 256; //ʹ���͵����ݲ�����8λ
    
    /* ����1 -----------------------------*/  
    if (Local_Key_User.key_state[1-1] == KEY_short)   Handle_Switch.Usart_OneDate = 1 ; 
   
    if( g_Addr > 6 ) g_Addr = 4;   
    if( g_Addr < 4 ) g_Addr = 6;   
    
    Key_FSM_Reset();
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
    int i;
  /* ADC6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/ 
  if( Handle_Switch.ADC6 )  Get_ADC6(); //ADC6�ɼ�

  /* �������ݴ���  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/ 
   if ( Handle_Switch.Usart_OneDate ) 
   {
        Handle_Switch.Usart_OneDate = 0;      
        RS485_Send_Date(RS485_SendBuff,RS485DATA_LENTH);
   }
   RS485_Receive_Date(ReceiveBuff);
                                                    
   if(Receive_Flag)         
   {     
    Receive_Flag = 0;  
    for(i = 0;i < 10;i++)  
    RS485_SendBuff[i] = ReceiveBuff[i];  
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
  
    unsigned char i;
    if( Handle_Switch.Show_Send_Receive )       
    {
        TM1640_Show_integer( RS485_SendBuff[RS485_Num] + (RS485_Num * 1000) ); 
        LED1_ON();   
    }
    
    else
    { 
        LED1_OFF();  
        TM1640_Show_integer( ReceiveBuff[RS485_Num] + (RS485_Num * 1000) ); 
    }
    

}


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

