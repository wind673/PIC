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
__Def_Key_FSM s_Local_Key_FSM ={ KEY_default,KEY_default,KEY_default,{0,0,0,0},{0,0,0,0} };//����һ��״̬���ṹ��
__Def_Key_FSM gs_Local_Key_User ={ KEY_default,KEY_default,KEY_default,{0,0,0,0},{0,0,0,0} };//����һ��״̬���ṹ��

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
  
    s_Local_Key_FSM.key_BUS = 0x00;//��ʼ������״̬
    //����������״
    if( KEY_1 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 0)  ; 
    if( KEY_2 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 1)  ; 
    if( KEY_3 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 2)  ; 
    if( KEY_4 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 3)  ; 
    if( KEY_5 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 4)  ; 
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_ScanFSM()     
* @Description   : ����״̬����ɨ�躯��
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/11/17
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_ScanFSM(void)
{
    Key_Scan();//ɨ�赱ǰ����״̬
    if( s_Local_Key_FSM.key_BUS & 0x01 ) s_Local_Key_FSM.a_key_count[0]++;  //�жϰ���1��״̬
    if( s_Local_Key_FSM.key_BUS & 0x02 ) s_Local_Key_FSM.a_key_count[1]++;  //�жϰ���2��״̬
    if( s_Local_Key_FSM.key_BUS & 0x04 ) s_Local_Key_FSM.a_key_count[2]++;  //�жϰ���3��״̬
    if( s_Local_Key_FSM.key_BUS & 0x08 ) s_Local_Key_FSM.a_key_count[3]++;  //�жϰ���4��״̬
    if( s_Local_Key_FSM.key_BUS & 0x10 ) s_Local_Key_FSM.a_key_count[4]++;  //�жϰ���5��״̬
     
}


/**----------------------------------------------------------------------------
* @Function_Name :Key_ReadFSM()
* @Description   :����״̬����ȡ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/14
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_ReadFSM(void)
{
    uchar key_num = KEY_NUMBER,key_num_mate;
            
    /* �����������ݴ��� =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/     
    while(key_num--) 
    {
        /* ��������״̬  --------------------------------*/ 
        if( s_Local_Key_FSM.key_BUS == 0x00 )  //��������״̬�����
        {
            if( s_Local_Key_FSM.a_key_count[key_num] > KEY_short_Time ) 
            {
                if( s_Local_Key_FSM.a_key_count[key_num] > KEY_hold_Time ) 
                gs_Local_Key_User.a_key_state[key_num] = KEY_long; //����������
                else  gs_Local_Key_User.a_key_state[key_num] = KEY_short;//�̰�
            }
            else gs_Local_Key_User.a_key_state[key_num] = KEY_default; 
            s_Local_Key_FSM.a_key_count[key_num] = 0; //���FSM�ڵļ����������¼���
        }
        /* �ð������ڱ����� -----------------------------*/ 
        else if( s_Local_Key_FSM.a_key_count[key_num] > KEY_hold_Time )            
        gs_Local_Key_User.a_key_state[key_num] = KEY_hold; //һֱ���� 
                
        /* �������������� -------------------------------*/ 
        else  gs_Local_Key_User.a_key_state[key_num] = KEY_busy;
    }
    
    /* ��ϰ������� =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/  
    
    for( key_num = 0;key_num < KEY_NUMBER - 1; key_num ++)//���������Ƚ�
    for( key_num_mate = key_num+1;key_num_mate < KEY_NUMBER ; key_num_mate ++)   
    if( gs_Local_Key_User.a_key_state[key_num] == gs_Local_Key_User.a_key_state[key_num_mate] ) 
    if(gs_Local_Key_User.a_key_state[key_num] != KEY_default)
    {  
        gs_Local_Key_User.key_group = (0x01 << key_num)|(0x01 << key_num_mate); 
        gs_Local_Key_User.key_group_state = gs_Local_Key_User.a_key_state[key_num];
    }
    
    
}

/**----------------------------------------------------------------------------
* @Function_Name :Key_ResetFSM()
* @Description   :����״̬����λ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/14
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_ResetFSM(void)
{
   uchar t;
   gs_Local_Key_User.key_BUS = 0x00;
   gs_Local_Key_User.key_group = KEY_default;
   t=4;
   while(t--) gs_Local_Key_User.a_key_count[t] = 0,
              gs_Local_Key_User.a_key_state[t] = KEY_default;
}


/**----------------------------------------------------------------------------
* @Function_Name :Key_ManageMessage()
* @Description   :������Ϣ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_ManageMessage(void)
{
    Key_ReadFSM();
    /* ��ϰ���2,4 ---------------------------*/  
    if ( gs_Local_Key_User.key_group == KEY_2_4 && gs_Local_Key_User.key_group_state ==  KEY_short ) 
    {
        gs_Handle_Switch.Show_Send_Receive = ~gs_Handle_Switch.Show_Send_Receive ; 
        Key_ResetFSM();  //������ϰ�������������������Ч
    }
    
    /* ����5 -----------------------------*/  
    if (gs_Local_Key_User.a_key_state[5-1] == KEY_short) g_RS485_Byte -- ; //�жϰ���5�Ƿ�̰�
    if (gs_Local_Key_User.a_key_state[5-1] == KEY_hold)  g_RS485_Byte -- ; //�жϰ���5�Ƿ񳤰�
    
    /* ����3 -----------------------------*/  
    if (gs_Local_Key_User.a_key_state[3-1] == KEY_short)  g_RS485_Byte ++ ; //�жϰ���3�Ƿ�̰�
    if (gs_Local_Key_User.a_key_state[3-1] == KEY_hold)   g_RS485_Byte ++ ; //�жϰ���3�Ƿ񳤰�
    
    if( g_RS485_Byte > 250 ) g_RS485_Byte = RS485DATA_LENTH - 1;
    else g_RS485_Byte %= RS485DATA_LENTH;     //ʹ���Ȳ����� RS485DATA_LENTH
    
    /* ����4 ------------------------------*/   
    if (gs_Local_Key_User.a_key_state[4-1] == KEY_short)  ga_RS485_SendBuff[g_RS485_Byte] ++ ; //�жϰ���4�Ƿ�̰�
    if (gs_Local_Key_User.a_key_state[4-1] == KEY_hold)  ga_RS485_SendBuff[g_RS485_Byte] ++ ; //�жϰ���4�Ƿ񳤰�
    
    /* ����2 ------------------------------*/  
    if (gs_Local_Key_User.a_key_state[2-1] == KEY_short)   ga_RS485_SendBuff[g_RS485_Byte] -- ; 
    if (gs_Local_Key_User.a_key_state[2-1] == KEY_hold)    ga_RS485_SendBuff[g_RS485_Byte] -- ; 
    
    ga_RS485_SendBuff[g_RS485_Byte] %= 256; //ʹ���͵����ݲ�����8λ
    
    /* ����1 -----------------------------*/  
    if (gs_Local_Key_User.a_key_state[1-1] == KEY_short)   gs_Handle_Switch.Usart_OneDate = 1 ; 
   
   
    Key_ResetFSM();    

}




/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/
