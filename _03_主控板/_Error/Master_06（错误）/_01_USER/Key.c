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
   /** ��������IO������Ϊ���� ------------------*/
    TRISC1 = 1;
    TRISF1 = 1;
    TRISF2 = 1;
    TRISA4 = 1;
    TRISA5 = 1;
    TRISF3 = 1;
    
    /** ������Ӧ����Ϊ�������� ----------------*/
    ANSEL4 = 0;
    ANSEL6 = 0;
    ANSEL7 = 0;
    ANSEL8 = 0;
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
    if( KEY_6 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 5)  ; 
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
    if( s_Local_Key_FSM.key_BUS & 0x20 ) s_Local_Key_FSM.a_key_count[5]++;  //�жϰ���5��״̬ 
    
}


/**----------------------------------------------------------------------------
* @Function_Name :Key_ReadFSM()
* @Description   :����״̬����ȡ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/14
* @Explain       : ��ȡ״̬��
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
* @Function_Name :Key_Inquiry()
* @Description   :������Ϣ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_Inquiry(void)
{
    Key_ReadFSM();
    /* ��ϰ���4,5 ---------------------------*/  
    if ( gs_Local_Key_User.key_group == KEY_4_5 && gs_Local_Key_User.key_group_state ==  KEY_short ) 
    {
        gs_Switch.a_Relay[g_RS485_Byte - 1] = 1;  //�̵�����         
        Key_ResetFSM();  //������ϰ�������������������Ч              
    }
    
    if ( gs_Local_Key_User.key_group == KEY_5_6 && gs_Local_Key_User.key_group_state ==  KEY_short ) 
    {
        
        gs_Switch.a_Relay[g_RS485_Byte - 1] = 0;//�̵�����
        Key_ResetFSM();  //������ϰ�������������������Ч
    }
    
    /* ����1�����ӣ�-----------------------------*/  
    if (gs_Local_Key_User.a_key_state[1-1] == KEY_short) g_RS485_Byte ++ ; // ���͵�����λ
    if (gs_Local_Key_User.a_key_state[1-1] == KEY_hold)  g_RS485_Byte ++ ; 
    
    /* ����2���˵���-----------------------------*/  
    if (gs_Local_Key_User.a_key_state[2-1] == KEY_short)   gs_Switch.Show_Send_Receive  = ~gs_Switch.Show_Send_Receive; //��ʾ�������ݻ��ǽ�������
    
    /* ����3����С -----------------------------*/  
    if (gs_Local_Key_User.a_key_state[3-1] == KEY_short)  g_RS485_Byte -- ; 
    if (gs_Local_Key_User.a_key_state[3-1] == KEY_hold)   g_RS485_Byte -- ; 
                             
    /* ����4����ţ�-----------------------------*/   
    if (gs_Local_Key_User.a_key_state[4-1] == KEY_short)  ga_RS485_SendBuff[g_RS485_Byte] ++ ; //���͵����� 
    if (gs_Local_Key_User.a_key_state[4-1] == KEY_hold)   ga_RS485_SendBuff[g_RS485_Byte] ++ ; 
                               
    /* ����5����ȫ��-----------------------------*/  
    if (gs_Local_Key_User.a_key_state[5-1] == KEY_short)                                                                                      
    gs_Switch.RS485_Reply = 1;//����һ������                                                                                  
                 
    /* ����6���˴ţ�-----------------------------*/  
    if (gs_Local_Key_User.a_key_state[6-1] == KEY_short)  ga_RS485_SendBuff[g_RS485_Byte] -- ;               
    if (gs_Local_Key_User.a_key_state[6-1] == KEY_hold)   ga_RS485_SendBuff[g_RS485_Byte] -- ;             
    
    
    /* ��Χ�ж�����------------------------------*/  
    if( g_RS485_Byte > 250 ) g_RS485_Byte = RS485_DATA_LENTH - 1;
    else g_RS485_Byte %= RS485_DATA_LENTH;     //ʹ���Ȳ����� RS485DATA_LENTH
    
    ga_RS485_SendBuff[g_RS485_Byte] %= 256; //ʹ���͵����ݲ�����8λ
    Key_ResetFSM();    

}




/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/
