/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : Key.c
* @Description : None
* @Date         : 2015/10/29
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "Key.h"
#include "GPIO.h"
#include "My_USART.h"
#include "Run.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/
static void Key_Scan(void);//����ɨ�躯����˽����

/* ȫ�ֱ������� ---------------------------------------------------------------*/
__Def_Key_FSM Local_Key_FSM ={ KEY_default,KEY_default,KEY_default,{0,0,0,0},{0,0,0,0} };//����һ��״̬���ṹ��
__Def_Key_FSM Local_Key_User ={ KEY_default,KEY_default,KEY_default,{0,0,0,0},{0,0,0,0} };//����һ��״̬���ṹ��

/* ȫ�ֺ�����д ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : Key_Init()     
* @Description   : �����ĳ�ʼ������
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/11/1
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_Init(void)
{
    TRISE |= 0x1e; //��E 2,3,4���ó�����(д��1�� | )
    TRISD |= 0xc0; //��D 6,7, ���ó�����(д��1�� | )
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_Scan()     
* @Description   : ������ɨ�躯��
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
static void Key_Scan(void)
{ 
  
    Local_Key_FSM.key_BUS = 0x00;//��ʼ������״̬
    //����������״
    if( KEY_1 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 0)  ; 
    if( KEY_2 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 1)  ; 
    if( KEY_3 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 2)  ; 
    if( KEY_4 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 3)  ; 
    if( KEY_5 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 4)  ; 
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_FSM_Scan()     
* @Description   : ����״̬����ɨ�躯��
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/11/17
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_FSM_Scan(void)
{
    Key_Scan();//ɨ�赱ǰ����״̬
    if( Local_Key_FSM.key_BUS & 0x01 ) Local_Key_FSM.key_count[0]++;  //�жϰ���1��״̬
    if( Local_Key_FSM.key_BUS & 0x02 ) Local_Key_FSM.key_count[1]++;  //�жϰ���2��״̬
    if( Local_Key_FSM.key_BUS & 0x04 ) Local_Key_FSM.key_count[2]++;  //�жϰ���3��״̬
    if( Local_Key_FSM.key_BUS & 0x08 ) Local_Key_FSM.key_count[3]++;  //�жϰ���4��״̬
    if( Local_Key_FSM.key_BUS & 0x10 ) Local_Key_FSM.key_count[4]++;  //�жϰ���5��״̬
     
}


/**----------------------------------------------------------------------------
* @Function_Name :Key_FSM_Read()
* @Description   :����״̬����ȡ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/14
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_FSM_Read(void)
{
    uchar key_num = KEY_NUMBER,key_num_mate;
            
    /* �����������ݴ��� =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/     
    while(key_num--) 
    {
        /* ��������״̬  --------------------------------*/ 
        if( Local_Key_FSM.key_BUS == 0x00 )  //��������״̬�����
        {
            if( Local_Key_FSM.key_count[key_num] > KEY_short_Time ) 
            {
                if( Local_Key_FSM.key_count[key_num] > KEY_hold_Time ) 
                Local_Key_User.key_state[key_num] = KEY_long; //����������
                else  Local_Key_User.key_state[key_num] = KEY_short;//�̰�
            }
            else Local_Key_User.key_state[key_num] = KEY_default; 
            Local_Key_FSM.key_count[key_num] = 0; //���FSM�ڵļ����������¼���
        }
        /* �ð������ڱ����� -----------------------------*/ 
        else if( Local_Key_FSM.key_count[key_num] > KEY_hold_Time )            
        Local_Key_User.key_state[key_num] = KEY_hold; //һֱ���� 
                
        /* �������������� -------------------------------*/ 
        else  Local_Key_User.key_state[key_num] = KEY_busy;
    }
    
    /* ��ϰ������� =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/  
    
    for( key_num = 0;key_num < KEY_NUMBER - 1; key_num ++)//���������Ƚ�
    for( key_num_mate = key_num+1;key_num_mate < KEY_NUMBER ; key_num_mate ++)   
    if( Local_Key_User.key_state[key_num] == Local_Key_User.key_state[key_num_mate] ) 
    if(Local_Key_User.key_state[key_num] != KEY_default)
    {  
        Local_Key_User.key_group = (0x01 << key_num)|(0x01 << key_num_mate); 
        Local_Key_User.key_group_state = Local_Key_User.key_state[key_num];
    }
    
    
}

/**----------------------------------------------------------------------------
* @Function_Name :Key_FSM_Reset()
* @Description   :����״̬����λ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/14
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_FSM_Reset(void)
{
   uchar t;
   Local_Key_User.key_BUS = 0x00;
   Local_Key_User.key_group = KEY_default;
   t=4;
   while(t--) Local_Key_User.key_count[t] = 0,
              Local_Key_User.key_state[t] = KEY_default;
}


/**----------------------------------------------------------------------------
* @Function_Name :Key_Message_Manage()
* @Description   :������Ϣ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_Message_Manage(void)
{
    Key_FSM_Read();
    /* ��ϰ���2,4 ---------------------------*/  
    if ( Local_Key_User.key_group == KEY_2_4 && Local_Key_User.key_group_state ==  KEY_short ) 
    {
        Handle_Switch.Show_Send_Receive = ~Handle_Switch.Show_Send_Receive ; 
        Key_FSM_Reset();  //������ϰ�������������������Ч
    }
    
    /* ����5 -----------------------------*/  
    if (Local_Key_User.key_state[5-1] == KEY_short)  RS485_Num -- ; //�жϰ���5�Ƿ�̰�
    if (Local_Key_User.key_state[5-1] == KEY_hold)  RS485_Num -- ; //�жϰ���5�Ƿ񳤰�
    
    /* ����3 -----------------------------*/  
    if (Local_Key_User.key_state[3-1] == KEY_short)    RS485_Num ++ ; //�жϰ���6�Ƿ�̰�
    if (Local_Key_User.key_state[3-1] == KEY_hold)    RS485_Num ++ ; //�жϰ���6�Ƿ񳤰�
    
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
   
   
    Key_FSM_Reset();    

}




/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/
