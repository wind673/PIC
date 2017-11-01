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
#include "Nixie.h"                     //LED��ʾ
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
    
    Key_FSM_Read();
    /* ��ϰ���1,2 ---------------------------*/  
    if ( Local_Key_User.key_group == KEY_1_2 && Local_Key_User.key_group_state ==  KEY_short )  
    {  
        Handle_Switch.Show_Send_Receive = ~Handle_Switch.Show_Send_Receive ; 
        Key_FSM_Reset(); Receive_Flag =1;
    }  
    
    /* ����1 -----------------------------*/  
    if (Local_Key_User.key_state[1-1] == KEY_short)  RS485_Num ++ ; //�жϰ���1�Ƿ�̰�
    if (Local_Key_User.key_state[1-1] == KEY_hold)  RS485_Num ++ ; //�жϰ���1�Ƿ񳤰�
   
    /* ����2 -----------------------------*/  
    if (Local_Key_User.key_state[2-1] == KEY_short)  RS485_Num -- ; //�жϰ���2�Ƿ�̰�
    if (Local_Key_User.key_state[2-1] == KEY_hold)  RS485_Num -- ; //�жϰ���2�Ƿ񳤰�
   
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
    Nixie_ShowNum(RS485_Num);  //��ʾ��λ
}


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

