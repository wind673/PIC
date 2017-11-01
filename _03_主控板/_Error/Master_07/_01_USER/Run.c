/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Run.c
* @Description : None
* @Date         : 2015/12/9
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : 工程的主要运行源文件
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
#include "Relay.h"                      //继电器
#include "SCR.h"                        //继电器       


/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/
unsigned char ReceiveBuff[RS485_DATA_LENTH]; //接收数据的用户缓存区

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/
__Switch_Def gs_Switch;    //各种开关结构体
__Msg_Def gsa_Msg[DEVICE_NUMBER] = {0};     //各种消息
__ComDataDef gs_ComData;                    //整个系统的公共数据容器

/* 全局函数编写 ---------------------------------------------------------------*/


/**----------------------------------------------------------------------------
* @Function_Name : ManageMessage()     
* @Description   : 处理函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void ManageMessage()
{
    RS485_Inquiry();        //RS485消息查询
    Key_Inquiry();          //本地按键消息查询  
    RS485_RecogniseMessage(ga_RS485_ReceiveBuff,RS485_DATA_LENTH);  //RS485消息识别分析
    RS485_AnalysisData();  //数据分析    
    
}
  
/**----------------------------------------------------------------------------
* @Function_Name : Manage_Incident()     
* @Description   : 运行函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Manage_Incident()
{
    unsigned int i;
  
  /* 回复消息 ----------------------------------------*/ 
  if ( gs_Switch.RS485_Reply ) 
  RS485_SendDate(ga_RS485_SendBuff,RS485_DATA_LENTH); //函数内部会清除标志位  
 
  /* 充磁 ----------------------------------------*/   
    for(i = 0; i< MAGNET_CH_NUMBER ;i++ )   
    if( gs_Switch.a_Magnet[i] == 1)   
    SCR_Magnet(i); //函数内部会清除标志位 
                                              
  /* 退磁 ----------------------------------------*/   
    for(i = 0; i< MAGNET_CH_NUMBER ;i++ )   
    if( gs_Switch.a_Magnet[i] == 1)   
    SCR_Demagnet(i); //函数内部会清除标志位 
    
    SCR_Demagnet(g_RS485_Byte);    
}


/**----------------------------------------------------------------------------
* @Function_Name : ShowResult()     
* @Description   : 显示函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void ShowResult()
{
    if( gs_Switch.Show_Send_Receive )       
    {
        TM1640_Show_integer( ga_RS485_SendBuff[g_RS485_Byte] + (g_RS485_Byte * 1000) ); 
        LED1_ON();    
    }
    
    else
    {
        TM1640_Show_integer( ga_RS485_ReceiveBuff[g_RS485_Byte] + (g_RS485_Byte * 1000) ); 
        LED1_OFF();                  
    }
    
    TM1640_Writer_Dates(4, LED_BUS);//刷新灯的状态
}


/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

