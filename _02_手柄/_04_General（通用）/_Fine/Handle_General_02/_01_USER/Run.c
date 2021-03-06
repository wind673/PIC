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
#include "Config_18F67K22.h"           //配置PIC芯片   
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
__Msg_Def Handle_Msg[10] = {0,{0}};     //各种消息
        

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
void Message_Manage()
{
    Key_Message_Manage();//本地按键消息处理
    RS485_Message_Manage(RS485_ReceiveBuff,RS485DATA_LENTH);//RS485消息处理
    
    
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

  /* 串口数据传输  =-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-*/ 
   if ( Handle_Switch.Usart_OneDate ) 
   {
        Handle_Switch.Usart_OneDate = 0;      
        RS485_Send_Date(RS485_SendBuff,RS485DATA_LENTH);
        
   }
  
  
 
     
  
}


/**----------------------------------------------------------------------------
* @Function_Name : Result_Show()     
* @Description   : 显示函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Result_Show()
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

