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

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/


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
    if (Key_FSM_Read(4) == KEY_short )  USART2_TendBuff ++;
    if (Key_FSM_Read(1) == KEY_short )  Handle_01_Switch.Usart_OneDate = 1; 
    if (Key_FSM_Read(2) == KEY_short )  USART2_TendBuff --;
        
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
  /*=-=-=-=-=-=-=-=-=-=-=-=- ADC6 =-=-=-=-=-=-=-=-=-=-=-*/ 
  if( Handle_01_Switch.ADC6 )  Get_ADC6(); //ADC6采集

  /*=-=-=-=-=-=-=-=-=-=-=-=- 串口数据传输  =-=-=-=-=-=-=-=-=-=-=-*/ 
   if ( Handle_01_Switch.Usart_OneDate ) 
   {
        Handle_01_Switch.Usart_OneDate = 0;      
        
        while( Busy2USART()); //等待Usart2空闲  
        RS485_ON();           //打开RS485             
        TXREG2 = USART2_TendBuff;   
        while( Busy2USART()); //等待Usart2发送完毕     
        RS485_OFF();           //关闭RS485
        
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
//    TM1640_Show_Decimal( ADC6_Buff ); //显示ADC采集的数据        
    
    TM1640_Show_integer( USART2_TendBuff );          
//    TM1640_Show_integer( USART2_ReceiveBuff ); 
}


/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

