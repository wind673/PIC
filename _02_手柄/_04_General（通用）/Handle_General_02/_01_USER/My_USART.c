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
#include "Run.h"
#include "Config_18F67K22.h"


/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/
static void CRC_Verify(unsigned char *DataBuff,unsigned char date_lenth);

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
    /* 装载起始码 ------------------------------------*/              
    date_dress[--date_lenth] = RS485_START;   
    
    /* 装载CRC校验码 ---------------------------------*/                       
    CRC_Verify(date_dress,RS485DATA_LENTH);  
    
    /* 准备发送 --------------------------------------*/        
    while( Busy2USART() );      //等待Usart2发送完毕    
    RS485_ON();    //打开RS485 
    
    /* 发送起始码 -----------------------------------*/
    TXREG2 = date_dress[date_lenth];           
    while( Busy2USART() );      //等待Usart2发送完毕  
    
    /* 发送数据位 -----------------------------------*/
    while( date_lenth --) 
    {
        if(date_dress[date_lenth] == RS485_START )  date_dress[date_lenth]--;//禁止出现起始码，若出现则修正
        TXREG2 = date_dress[date_lenth];   
        while( Busy2USART()); //等待Usart2发送完毕     
    }
    
    RS485_OFF(); //关闭RS485
}

/**----------------------------------------------------------------------------
 * @Function_Name : RS485_Message_Manage( )
 * @Description   : RS485消息分析处理
 * @Parameter     : DataBuff[]：RS485所接收的一帧数据 
 *                    date_lenth：一帧数据的长度
 * @Return        : char
 * @Programer     : WindRises（谢玉伸）
 * @Data          : 2015/12/13
 * @Explain       : 接收成功返回1  否则返回0
------------------------------------------------------------------------------*/
unsigned char  RS485_Message_Manage( unsigned char DataBuff[] ,unsigned char date_lenth )
{
     unsigned char CRC_H,CRC_L,from_dress;
     if( RS485_Receive_Flag == 1 )
     {
     
            /* 判断起始码 ---------------------------------*/  
            if( DataBuff [date_lenth-1] != 0xaa)  { RS485_Receive_Flag = 0; return 1;}  //起始码错误      

            /* 判断CRC校验码 ------------------------------*/        
            CRC_H = DataBuff[1];  //转存CRC校验码
            CRC_L = DataBuff[0];
            CRC_Verify(DataBuff,RS485DATA_LENTH);  
            if( DataBuff[1] != CRC_H ) { RS485_Receive_Flag = 0; return 2 ;} //CRC校验错误
            if( DataBuff[0] != CRC_L ) { RS485_Receive_Flag = 0; return 2 ;} 

            /* 判断地址 ----------------------------------*/
            if( ( DataBuff[date_lenth - 2] != Local_Address )  && ( DataBuff[date_lenth - 2] != All_Address) ) { RS485_Receive_Flag = 0; return 3;}//非本机地址

            /* 判断发送方硬件类型 --------------------------*/
            from_dress = DataBuff[date_lenth - 3];
            if( from_dress < 0x10 )  Handle_Msg[from_dress].Hardware_Type = Type_HANDLE; // 手柄:0x00~0x0f
            else if( from_dress < 0x20 )  Handle_Msg[from_dress].Hardware_Type = Type_MASTER; //主板:0x10~0x1f
            else if( from_dress < 0x30 )  Handle_Msg[from_dress].Hardware_Type = Type_SENSOR; //传感器:0x20~0x2f

            /* 转存数据 -----------------------------------*/
            Handle_Msg[from_dress].Order = DataBuff[date_lenth - 4]; //转存指令
            Handle_Msg[from_dress].Parameter[3] =  DataBuff[date_lenth -5]; //转存参数       
            Handle_Msg[from_dress].Parameter[2] =  DataBuff[date_lenth -6];
            Handle_Msg[from_dress].Parameter[1] =  DataBuff[date_lenth -7];
            Handle_Msg[from_dress].Parameter[0] =  DataBuff[date_lenth -8];

            /* 处理完毕 -----------------------------------*/
            Handle_Msg[from_dress].hand_info = 1;//数据处理完毕
            RS485_Receive_Flag = 0;
     }
}


/**----------------------------------------------------------------------------
 * @Function_Name : CRC_Verify(unsigned char *DataBuff)
 * @Description   : CRC校验码生成
 * @Parameter     : *DataBuff ：需要CRC转换的数组
 *                    date_lenth：转换的数组长度
 * @Return        :  void
 * @Programer     : WindRises（谢玉伸）
 * @Data          : 2015/12/13
 * @Explain       : 转换CRC值(2byte)
------------------------------------------------------------------------------*/
static void CRC_Verify(unsigned char *DataBuff,unsigned char date_lenth)
{
    unsigned long int CRC_Value = 0;
    uchar CRC_Byte;
    
    for(CRC_Byte = 2; CRC_Byte < date_lenth ;CRC_Byte++)
    CRC_Value  =  ( CRC_Value + DataBuff[CRC_Byte]*CRC_Byte ) % CRC_CODE;           
    
    DataBuff[1] = CRC_Value/0xff;  
    DataBuff[0] = CRC_Value%0xff; //传递参数
    
    if( DataBuff[1] == RS485_START ) DataBuff[1] --;//避免出现 起始码
    if( DataBuff[0] == RS485_START ) DataBuff[0] --;
      
}

/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/





