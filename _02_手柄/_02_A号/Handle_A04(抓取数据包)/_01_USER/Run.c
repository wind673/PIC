/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Run.c
* @Description : None
* @Date         : 2015/12/9
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include "Run.h"
#include <pic18f67k22.h>                //PIC官方函数库
#include "Config_18F167K22.h"           //配置PIC芯片   
#include "My_Delay.h"                   //延时
#include "GPIO.h"                       //GPIO口的配置
#include "My_Types.h"                   //自定义的习惯写法定义
#include "Key.h"                        //简写定义
#include "TM1640.h"                     //LED显示
#include "My_ADC.h"                     //ADC
#include "My_Timer.h"                   //定时器
#include "My_USART.h"                   //串口 
#include "usart.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/
unsigned char ReceiveBuff[RS485DATA_LENTH]; //接收数据的用户缓存区

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/
__Switch_Def Handle_Switch = {0,0,0,0}; //各种开关结构体

/* 全局函数编写 ---------------------------------------------------------------*/


/**----------------------------------------------------------------------------
* @Function_Name : Manage_Message()     
* @Description   : 处理函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Manage_Message()
{
    Key_FSM_Read();
    /* 按键5 -----------------------------*/  
    if (Local_Key_User.key_state[5-1] == KEY_short)  RS485_Num -- ; //判断按键5是否短按
    if (Local_Key_User.key_state[5-1] == KEY_hold)  RS485_Num -- ; //判断按键5是否长按
    
    /* 按键3 -----------------------------*/  
    if (Local_Key_User.key_state[3-1] == KEY_short)    RS485_Num ++ ; //判断按键6是否短按
    if (Local_Key_User.key_state[3-1] == KEY_hold)    RS485_Num ++ ; //判断按键6是否长按
    
    if( RS485_Num > 250 ) RS485_Num = RS485DATA_LENTH - 1;
    else RS485_Num %= RS485DATA_LENTH;     //使长度不超多 RS485DATA_LENTH
    
    /* 按键4 ------------------------------*/   
    if (Local_Key_User.key_state[4-1] == KEY_short)  RS485_SendBuff[RS485_Num] ++ ; //判断按键4是否短按
    if (Local_Key_User.key_state[4-1] == KEY_hold)  RS485_SendBuff[RS485_Num] ++ ; //判断按键4是否长按
    
    /* 按键2 ------------------------------*/  
    if (Local_Key_User.key_state[2-1] == KEY_short)   RS485_SendBuff[RS485_Num] -- ; 
    if (Local_Key_User.key_state[2-1] == KEY_hold)    RS485_SendBuff[RS485_Num] -- ; 
    
    RS485_SendBuff[RS485_Num] %= 256; //使发送的数据不超过8位
    
    /* 按键1 -----------------------------*/  
    if (Local_Key_User.key_state[1-1] == KEY_short)   Handle_Switch.Usart_OneDate = 1 ; 
   
    /* 组合按键2,4 ---------------------------*/  
    if ( Local_Key_User.key_group == KEY_2_4 && Local_Key_User.key_group_state ==  KEY_short )    Handle_Switch.Show_Send_Receive = ~Handle_Switch.Show_Send_Receive ; 
   
    Key_FSM_Reset();
}


/**----------------------------------------------------------------------------
* @Function_Name : Running()     
* @Description   : 运行函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Run()
{
  /* ADC6 =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/ 
  if( Handle_Switch.ADC6 )  Get_ADC6(); //ADC6采集

  /* 串口数据传输  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/ 
   if ( Handle_Switch.Usart_OneDate ) 
   {
        Handle_Switch.Usart_OneDate = 0;      
        RS485_Send_Date(RS485_SendBuff,RS485DATA_LENTH);
   }
   
  
  
}


/**----------------------------------------------------------------------------
* @Function_Name : Show_Result()     
* @Description   : 显示函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Show_Result()
{
    if( Handle_Switch.Show_Send_Receive )       
    {
        TM1640_Show_integer( RS485_SendBuff[RS485_Num] + (RS485_Num * 1000) ); 
        LED1_ON();   
    }
    
    else
    {
        TM1640_Show_integer( RS485_ReceiveBuff[RS485_Num] + (RS485_Num * 1000) ); 
        LED1_OFF();                  
    }
    

}


/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

