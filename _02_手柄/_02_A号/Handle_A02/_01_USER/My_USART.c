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
#include <math.h>

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/
static unsigned int CRC_Verify(unsigned char *DataBuff);

/* 全局变量定义 ---------------------------------------------------------------*/
unsigned char RS485_SendBuff[RS485DATA_LENTH] = {0};      //RS485发送数据缓存区
unsigned char RS485_ReceiveBuff[RS485DATA_LENTH] = {0};   //RS485接收数据缓存区
unsigned char RS485_Receive_Flag = 0;                     //RS485接收完成标志
unsigned char RS485_Num = 0;                       //RS485字节位


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
    RS485_OFF();               //RS485初始化为接收状态
    ANCON2 &= 0XF1;            //关闭GPIO1,2，3的模拟输入
}



/**----------------------------------------------------------------------------
* @Function_Name : RS485_Send_Date(unsigned char *date_dress, unsigned char date_lenth)
* @Description   : 发送串口2的数据
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/10/29
* @Explain       : 先发高位再发低位
------------------------------------------------------------------------------*/
void RS485_Send_Date(unsigned char *date_dress, unsigned char date_lenth)
{
    unsigned int temp;
    while( Busy2USART()); //等待Usart2空闲  
    RS485_ON();           //打开RS485    
    
    /* 发送起始码 --------------------------------------*/
    TXREG2 = 0xaa;//起始码 
    date_lenth --;
    while( Busy2USART()); //等待Usart2发送完毕     
    
    /* 发送数据位 --------------------------------------*/
    while( (date_lenth --) -2 )
    {
        TXREG2 = date_dress[date_lenth];   
        while( Busy2USART()); //等待Usart2发送完毕     
    }
    
    /* 发送CRC校验码 ------------------------------------*/
    date_dress[RS485DATA_LENTH - 1] = 0xaa;
    temp = CRC_Verify(date_dress);
    TXREG2 = temp / 0xff; 
    while( Busy2USART()); //等待Usart2发送完毕     
    TXREG2 = temp % 0xff; 
    while( Busy2USART()); //等待Usart2发送完毕     
    
    RS485_OFF();           //关闭RS485
}

/**----------------------------------------------------------------------------
* @Function_Name : RS485_Receive_Date( unsigned char DataBuff[] )
* @Description   : RS485接收数据
* @Parameter     : void
* @Return        : char
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/13
* @Explain       : 接收成功返回1  否则返回0
------------------------------------------------------------------------------*/
unsigned char  RS485_Receive_Date( unsigned char DataBuff[] )
{
    unsigned n = RS485DATA_LENTH - 1;
    unsigned int temp;
    
    if(RS485_Receive_Flag)
    {
        RS485_Receive_Flag = 0;//清除标志位
        while ( n --)//从接收缓存区转存用户缓存区
        DataBuff[n] = RS485_ReceiveBuff[n];
         
        return 1;
    }
    else return 0;
}


/**----------------------------------------------------------------------------
* @Function_Name : CRC_Verify(unsigned char *DataBuff)
* @Description   : CRC校验码生成
* @Parameter     : unsigned char *DataBuff 
* @Return        : CRC_Value //转换后的CRC值
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/13
* @Explain       : 接收成功返回1  否则返回0
------------------------------------------------------------------------------*/
static unsigned int CRC_Verify(unsigned char *DataBuff)
{
    unsigned long int CRC_Value ;
    unsigned char CRC_Byte = RS485DATA_LENTH - 1 ;  
    
    while((CRC_Byte --) -2)//对9~2位进行校验
    CRC_Value +=  pow(DataBuff[CRC_Byte],CRC_Byte);
    CRC_Value %= CRC_CODE;
    return CRC_Value;//返回转换值
}

/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/





