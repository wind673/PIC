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

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/
static void Key_Scan(void);//按键扫描函数的私定义

/* 全局变量定义 ---------------------------------------------------------------*/
__Def_Key_FSM Local_Key_FSM ={ KEY_default,KEY_default,KEY_default,{0},{0} };//定义一个状态机结构体
__Def_Key_FSM Local_Key_User ={ KEY_default,KEY_default,KEY_default,{0},{0} };//定义一个状态机结构体

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
    TRISFbits.TRISF2 = 1;   
    TRISFbits.TRISF3 = 1;   
    ANSEL11 = 0;  
    ANSEL10 = 0;  
    
 
    
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
  
    Local_Key_FSM.key_BUS = 0x00;//初始化按键状态
    //检测各按键现状
    if( KEY_1 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 0)  ; 
    if( KEY_2 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 1)  ; 
//    if( KEY_3 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 2)  ; 
//    if( KEY_4 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 3)  ; 
//    if( KEY_5 == 0 )  Local_Key_FSM.key_BUS |= (0x01 << 4)  ; 
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_FSM_Scan()     
* @Description   : 按键状态机的扫描函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/11/17
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_FSM_Scan(void)
{
    Key_Scan();//扫描当前按键状态
    if( Local_Key_FSM.key_BUS & 0x01 ) Local_Key_FSM.key_count[0]++;  //判断按键1的状态
    if( Local_Key_FSM.key_BUS & 0x02 ) Local_Key_FSM.key_count[1]++;  //判断按键2的状态
//    if( Local_Key_FSM.key_BUS & 0x04 ) Local_Key_FSM.key_count[2]++;  //判断按键3的状态
//    if( Local_Key_FSM.key_BUS & 0x08 ) Local_Key_FSM.key_count[3]++;  //判断按键4的状态
//    if( Local_Key_FSM.key_BUS & 0x10 ) Local_Key_FSM.key_count[4]++;  //判断按键5的状态
      
}


/**----------------------------------------------------------------------------
* @Function_Name :Key_FSM_Read()
* @Description   :按键状态机读取函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/14
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_FSM_Read(void)
{
    uchar key_num = KEY_NUMBER,key_num_mate;
            
    /* 单个按键数据处理 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/     
    while(key_num--) 
    {
        /* 按键空闲状态  --------------------------------*/ 
        if( Local_Key_FSM.key_BUS == 0x00 )  //按键空闲状态情况下
        {
            if( Local_Key_FSM.key_count[key_num] > KEY_short_Time ) 
            {
                if( Local_Key_FSM.key_count[key_num] > KEY_hold_Time ) 
                Local_Key_User.key_state[key_num] = KEY_long; //长按后松手
                else  Local_Key_User.key_state[key_num] = KEY_short;//短按
            }
            else Local_Key_User.key_state[key_num] = KEY_default; 
            Local_Key_FSM.key_count[key_num] = 0; //清除FSM内的计数器，重新计数
        }
        /* 该按键正在被按下 -----------------------------*/ 
        else if( Local_Key_FSM.key_count[key_num] > KEY_hold_Time )            
        Local_Key_User.key_state[key_num] = KEY_hold; //一直长按 
                
        /* 其他按键被按下 -------------------------------*/ 
        else  Local_Key_User.key_state[key_num] = KEY_busy;
    }
    
    /* 组合按键数据 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/  
    
    for( key_num = 0;key_num < KEY_NUMBER - 1; key_num ++)//进行两两比较
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
* @Description   :按键状态机复位函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
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


/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
