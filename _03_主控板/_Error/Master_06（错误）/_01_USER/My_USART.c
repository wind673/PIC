/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : My_USART.c
* @Description : 串口通讯源文件
* @Date         : 2015/10/29
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : 串口功能实现源文件
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "My_USART.h"
#include "usart.h"
#include <math.h>
#include "Run.h"
#include "Config_18F67K22.h"
#include "Relay.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/

/* 全局函数编写 ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : My_USART_Init()     
* @Description   : 串口通信初始化
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
void RS485_Init()
{
    Open1USART( USART_TX_INT_OFF  &
                 USART_RX_INT_ON   &
                 USART_ASYNCH_MODE &
                 USART_EIGHT_BIT   &
                 USART_CONT_RX     &
                 USART_BRGH_LOW    
                ,
                 12 //波特率为：9600
                );
    
    TRISC7 = 1;     //RX1 设置为输入             
    TRISC6 = 0;     //TX1 设置为输出
    TRISC0 = 0;     //RS485CON 设置为输出
    RS485_OFF();    //RS485初始化为接收状态
    
}



/**---------------------------------------------------------------------------- 
 * @Function_Name : RS485_SendDate(unsigned char *date_dress, unsigned char date_lenth)
 * @Description   : 发送串口1的数据
 * @Parameter     : void
 * @Return        : void
 * @Programer     : WindRises（谢玉伸）
 * @Data          : 2015/10/29
 * @Explain       : 先发高位再发低位
------------------------------------------------------------------------------*/
void RS485_SendDate(unsigned char *date_dress, unsigned char date_lenth)
{
    /* 装载起始码 ------------------------------------*/              
    date_dress[--date_lenth] = RS485_START;   
    
    /* 装载CRC校验码 ---------------------------------*/                       
    VerifyCRC(date_dress,date_lenth);  
    
    /* 准备发送 --------------------------------------*/        
    while( Busy1USART() );      //等待Usart1发送完毕    
    RS485_ON();    //打开RS485 
    
    /* 发送起始码 -----------------------------------*/
    TXREG1 = date_dress[date_lenth];           
    while( Busy1USART() );      //等待Usart1发送完毕  
    
    /* 发送数据位 -----------------------------------*/
    while( date_lenth --) 
    {
        if(date_dress[date_lenth] == RS485_START )  date_dress[date_lenth]--;    //禁止出现起始码，若出现则修正
        TXREG1 = date_dress[date_lenth];   
        while( Busy1USART()); //等待Usart1发送完毕     
    }
    
    RS485_OFF(); //关闭RS485
    gs_Switch.RS485_Reply = 0; //发送完毕
}

        
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/





