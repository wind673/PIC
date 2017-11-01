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
#include "My_Types.h"                   //�Զ����ϰ��д������
#include "Key.h"                        //��д����
#include "Nixie.h"                     //LED��ʾ
#include "My_Timer.h"                   //��ʱ��
#include "IR2184.h"   
#include "EEPROM.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/  

/* ˽�У���̬���������� --------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 
unsigned int IR2184_Timer = 0;

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 
extern unsigned char IR2184_Num;
extern unsigned char Nix_Flash;

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
void Manage_Message(void)
{
    unsigned char _databuff[1] = {0};
    
    Key_FSM_Read();
    /* ��ϰ���1,2 ------------------------*/  
    if ( Local_Key_User.key_group == KEY_1_2 && Local_Key_User.key_group_state ==  KEY_short )  
    {   
        _databuff[0] = IR2184_Num ;
        EEPROM_Writers(0x10,_databuff,1); //�洢������
        Nix_Flash = 130;  //��˸ʱ�� 130*10ms =1.3s
    }                   
    
    /* ����1 -----------------------------*/  
    if (Local_Key_User.key_state[1-1] == KEY_short)  IR2184_Num -- ; //�жϰ���1�Ƿ�̰�
    if (Local_Key_User.key_state[1-1] == KEY_hold)   IR2184_Num -- ; //�жϰ���1�Ƿ񳤰�
    
    /* ����2 -----------------------------*/  
    if (Local_Key_User.key_state[2-1] == KEY_short)  IR2184_Num ++ ; //�жϰ���2�Ƿ�̰�
    if (Local_Key_User.key_state[2-1] == KEY_hold)   IR2184_Num ++ ; //�жϰ���2�Ƿ񳤰�
   
    if(IR2184_Num > 99 && IR2184_Num <200 ) IR2184_Num = 0;
    if(IR2184_Num > 200 ) IR2184_Num = 99;
    
    Key_FSM_Reset();
}


/**----------------------------------------------------------------------------
* @Function_Name : Run()     
* @Description   : ���к���
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Run(void)
{
    if( IR2184_INPUT_1 == 0 ) 
    {
        delay_ms(20);  //20ms������ȥ����
        if( IR2184_INPUT_1 == 0 ) 
        {
            IR2184_Timer = 0;         
            IR2184_ON_1();      
            while( IR2184_Timer < IR2184_Num ); 
            IR2184_OFF_1(); 
        }
         
    }
    
    if( IR2184_INPUT_2 == 0 ) 
    {
        delay_ms(20);  //20ms������ȥ����
        if( IR2184_INPUT_2 == 0 )
        {
            IR2184_Timer = 0;
            IR2184_ON_2(); 
            while( IR2184_Timer < IR2184_Num );
            IR2184_OFF_2(); 
        }
        
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
void Show_Result(void)
{ 
    Nixie_ShowNum(IR2184_Num);  //��ʾ��λ
}

/**----------------------------------------------------------------------------
* @Function_Name : Sys_Init()     
* @Description   : ϵͳ��ʼ������
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2016/2/21
* @Explain       : None
------------------------------------------------------------------------------*/
void Sys_Init(void)
{
    /* �������� --------------------------------*/
    unsigned char _databuff[1] = {0};
    
    /* ��ʼ�� --------------------------------*/
    WDTCON = 1;    //�������Ź�
    CLRWDT();
    Key_Init();       //����     
    Timer0_Init();    //��ʱ��   
    Nixie_Init();     //�����
    IR2184_Init();    //���ٰ��ż�����
    Key_Init();        //������ʼ��
    
    EEPROM_Reads(0x10,_databuff,1); //��ȡ�洢������
    IR2184_Num = _databuff[0];
    

}

/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

