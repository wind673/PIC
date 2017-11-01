/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : My_USART.c
* @Description : 串口通讯源文件
* @Date         : 2015/10/29
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "My_USART.h"
#include "usart.h"
/* 私有宏定义 -----------------------------------------------------------------*/
/* 开关全局中断的宏 ---------------------------------------------------------- */
#define _rn_EN_ALLINT()     INTCON |= 0x80				   /* 使能全局中断     */
#define _rn_DIS_ALLINT()	INTCON &= 0x7f				   /* 禁止全局中断 	  */
#define _rn_EN_PERINT()     INTCON |= 0x40				   /* 使能外设中断     */
#define _rn_DIS_PERINT()	INTCON &= 0xbf				   /* 禁止外设中断 	  */
/* DE RE 开关位 --------------------------------------------------- */
#define RS485_TX_EN()     PORTGbits.RG3 = 0
#define RS485_RX_EN()     PORTGbits.RG3 = 1
 
/* 私有变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/
unsigned int USART2_TendBuff = 0;
unsigned int USART2_ReceiveBuff = 0;
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
void My_USART_Init()
{
    Open2USART( USART_TX_INT_OFF  &
                 USART_RX_INT_ON   &
                 USART_ASYNCH_MODE &
                 USART_EIGHT_BIT   &
                 USART_CONT_RX     &
                 USART_BRGH_LOW    
                ,
                 12 //波特率为：9600
                );
    
    TRISGbits.TRISG1 = 1;     //RG1:RX2 设置为输入             
    TRISGbits.TRISG2 = 0;     //RG2:TX2 设置为输出
    TRISGbits.TRISG3 = 0;     //RG3:RS485CON 设置为输出
    RS485_RX();                //RS485初始化为接收状态
    
    INTCON |= 0x80;
    INTCON |= 0x40;
    
    ANCON2 &= 0XF9; 
 
}

void Write2USART(char data)
{
  if(TXSTA2bits.TX9)  // 9-bit mode?
  {
    TXSTA2bits.TX9D = 0;       // Set the TX9D bit according to the
    if(USART2_Status.TX_NINE)  // USART2 Tx 9th bit in status reg
      TXSTA2bits.TX9D = 1;
  }
  
  TXREG2 = data;      // Write the data byte to the USART2
}


/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/





