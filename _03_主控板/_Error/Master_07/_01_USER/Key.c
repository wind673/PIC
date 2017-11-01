/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Key.c
* @Description : None
* @Date         : 2015/10/29
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "Key.h"
#include "GPIO.h"
#include "My_USART.h"
#include "Run.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/
static void Key_Scan(void);//按键扫描函数的私定义

/* 全局变量定义 ---------------------------------------------------------------*/
__Def_Key_FSM s_Local_Key_FSM ={ KEY_default,KEY_default,KEY_default,{0,0,0,0},{0,0,0,0} };//定义一个状态机结构体
__Def_Key_FSM gs_Local_Key_User ={ KEY_default,KEY_default,KEY_default,{0,0,0,0},{0,0,0,0} };//定义一个状态机结构体

/* 全局函数编写 ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : Key_Init()     
* @Description   : 按键的初始化函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/11/1
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_Init(void)
{
   /** 将按键的IO口配置为输入 ------------------*/
    TRISC1 = 1;
    TRISF1 = 1;
    TRISF2 = 1;
    TRISA4 = 1;
    TRISA5 = 1;
    TRISF3 = 1;
    
    /** 设置相应引脚为数字引脚 ----------------*/
    ANSEL4 = 0;
    ANSEL6 = 0;
    ANSEL7 = 0;
    ANSEL8 = 0;
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_Scan()     
* @Description   : 按键的扫描函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
static void Key_Scan(void)
{ 
    s_Local_Key_FSM.key_BUS = 0x00;//初始化按键状态
    //检测各按键现状
    if( KEY_1 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 0)  ; 
    if( KEY_2 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 1)  ; 
    if( KEY_3 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 2)  ; 
    if( KEY_4 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 3)  ; 
    if( KEY_5 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 4)  ; 
    if( KEY_6 == 0 )  s_Local_Key_FSM.key_BUS |= (0x01 << 5)  ; 
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_ScanFSM()     
* @Description   : 按键状态机的扫描函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/11/17
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_ScanFSM(void)
{
    Key_Scan();//扫描当前按键状态
    if( s_Local_Key_FSM.key_BUS & 0x01 ) s_Local_Key_FSM.a_key_count[0]++;  //判断按键1的状态
    if( s_Local_Key_FSM.key_BUS & 0x02 ) s_Local_Key_FSM.a_key_count[1]++;  //判断按键2的状态
    if( s_Local_Key_FSM.key_BUS & 0x04 ) s_Local_Key_FSM.a_key_count[2]++;  //判断按键3的状态
    if( s_Local_Key_FSM.key_BUS & 0x08 ) s_Local_Key_FSM.a_key_count[3]++;  //判断按键4的状态
    if( s_Local_Key_FSM.key_BUS & 0x10 ) s_Local_Key_FSM.a_key_count[4]++;  //判断按键5的状态
    if( s_Local_Key_FSM.key_BUS & 0x20 ) s_Local_Key_FSM.a_key_count[5]++;  //判断按键5的状态 
    
}


/**----------------------------------------------------------------------------
* @Function_Name :Key_ReadFSM()
* @Description   :按键状态机读取函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/14
* @Explain       : 读取状态机
------------------------------------------------------------------------------*/
void Key_ReadFSM(void)
{
    uchar key_num = KEY_NUMBER,key_num_mate;
            
    /* 单个按键数据处理 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/     
    while(key_num--) 
    {
        /* 按键空闲状态  --------------------------------*/ 
        if( s_Local_Key_FSM.key_BUS == 0x00 )  //按键空闲状态情况下
        {
            if( s_Local_Key_FSM.a_key_count[key_num] > KEY_short_Time ) 
            {
                if( s_Local_Key_FSM.a_key_count[key_num] > KEY_hold_Time ) 
                gs_Local_Key_User.a_key_state[key_num] = KEY_long; //长按后松手
                else  gs_Local_Key_User.a_key_state[key_num] = KEY_short;//短按
            }
            else gs_Local_Key_User.a_key_state[key_num] = KEY_default; 
            s_Local_Key_FSM.a_key_count[key_num] = 0; //清除FSM内的计数器，重新计数
        }
        /* 该按键正在被按下 -----------------------------*/ 
        else if( s_Local_Key_FSM.a_key_count[key_num] > KEY_hold_Time )            
        gs_Local_Key_User.a_key_state[key_num] = KEY_hold; //一直长按 
                
        /* 其他按键被按下 -------------------------------*/ 
        else  gs_Local_Key_User.a_key_state[key_num] = KEY_busy;
    }
    
    /* 组合按键数据 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/  
    for( key_num = 0;key_num < KEY_NUMBER - 1; key_num ++)//进行两两比较
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
* @Description   :按键状态机复位函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
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
* @Description   :按键消息处理
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_Inquiry(void)
{
    Key_ReadFSM();
    /* 组合按键4,5 ---------------------------*/  
    if ( gs_Local_Key_User.key_group == KEY_4_5 && gs_Local_Key_User.key_group_state ==  KEY_short ) 
    {
        gs_Switch.a_Relay[g_RS485_Byte - 1] = 1;  //继电器开         
        Key_ResetFSM();  //读完组合按键，则其他按键皆无效              
    }
    
    if ( gs_Local_Key_User.key_group == KEY_5_6 && gs_Local_Key_User.key_group_state ==  KEY_short ) 
    {
        
        gs_Switch.a_Relay[g_RS485_Byte - 1] = 0;//继电器关
        Key_ResetFSM();  //读完组合按键，则其他按键皆无效
    }
    
    /* 按键1（增加）-----------------------------*/  
    if (gs_Local_Key_User.a_key_state[1-1] == KEY_short) g_RS485_Byte ++ ; // 发送的数据位
    if (gs_Local_Key_User.a_key_state[1-1] == KEY_hold)  g_RS485_Byte ++ ; 
    
    /* 按键2（菜单）-----------------------------*/  
    if (gs_Local_Key_User.a_key_state[2-1] == KEY_short)   gs_Switch.Show_Send_Receive  = ~gs_Switch.Show_Send_Receive; //显示发送数据还是接收数据
    
    /* 按键3（减小 -----------------------------*/  
    if (gs_Local_Key_User.a_key_state[3-1] == KEY_short)  g_RS485_Byte -- ; 
    if (gs_Local_Key_User.a_key_state[3-1] == KEY_hold)   g_RS485_Byte -- ; 
                             
    /* 按键4（充磁）-----------------------------*/   
    if (gs_Local_Key_User.a_key_state[4-1] == KEY_short)  ga_RS485_SendBuff[g_RS485_Byte] ++ ; //发送的数据 
    if (gs_Local_Key_User.a_key_state[4-1] == KEY_hold)   ga_RS485_SendBuff[g_RS485_Byte] ++ ; 
                               
    /* 按键5（安全）-----------------------------*/  
    if (gs_Local_Key_User.a_key_state[5-1] == KEY_short)                                                                                      
    gs_Switch.RS485_Reply = 1;//发送一组数据                                                                                  
                 
    /* 按键6（退磁）-----------------------------*/  
    if (gs_Local_Key_User.a_key_state[6-1] == KEY_short)  ga_RS485_SendBuff[g_RS485_Byte] -- ;               
    if (gs_Local_Key_User.a_key_state[6-1] == KEY_hold)   ga_RS485_SendBuff[g_RS485_Byte] -- ;             
    
    
    /* 范围判断修正------------------------------*/  
    if( g_RS485_Byte > 250 ) g_RS485_Byte = RS485_DATA_LENTH - 1;
    else g_RS485_Byte %= RS485_DATA_LENTH;     //使长度不超多 RS485DATA_LENTH
    
    ga_RS485_SendBuff[g_RS485_Byte] %= 256; //使发送的数据不超过8位
    Key_ResetFSM();    

}




/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
