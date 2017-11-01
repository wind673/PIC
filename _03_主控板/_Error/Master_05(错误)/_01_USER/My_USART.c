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
static void VerifyCRC(unsigned char *DataBuff,unsigned char date_lenth);

/* 全局变量定义 ---------------------------------------------------------------*/
unsigned char ga_RS485_SendBuff[RS485_DATA_LENTH] = {0};      //RS485发送数据缓存区
unsigned char ga_RS485_ReceiveBuff[RS485_DATA_LENTH] = {0};   //RS485接收数据缓存区
unsigned char g_RS485_Receive_Flag = 0;                       //RS485接收完成标志
unsigned char g_RS485_Byte = 0;                               //RS485字节位
unsigned char g_RS485_Send_Flag = 0;                          //RS485发送完成标志

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
 * @Description   : 发送串口2的数据
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
    while( Busy1USART() );      //等待Usart2发送完毕    
    RS485_ON();    //打开RS485 
    
    /* 发送起始码 -----------------------------------*/
    TXREG1 = date_dress[date_lenth];           
    while( Busy1USART() );      //等待Usart2发送完毕  
    
    /* 发送数据位 -----------------------------------*/
    while( date_lenth --) 
    {
        if(date_dress[date_lenth] == RS485_START )  date_dress[date_lenth]--;    //禁止出现起始码，若出现则修正
        TXREG1 = date_dress[date_lenth];   
        while( Busy1USART()); //等待Usart2发送完毕     
    }
    
    RS485_OFF(); //关闭RS485
}

/**----------------------------------------------------------------------------
 * @Function_Name : RS485_ManageMessage( )
 * @Description   : RS485消息处理转存
 * @Parameter     : DataBuff[]：RS485所接收的一帧数据 
 *                    date_lenth：一帧数据的长度
 * @Return        : char
 * @Programer     : WindRises（谢玉伸）
 * @Data          : 2015/12/13
 * @Explain       : 接收成功返回1  否则返回0
------------------------------------------------------------------------------*/
unsigned char  RS485_ManageMessage( unsigned char DataBuff[] ,unsigned char date_lenth )
{
     unsigned char CRC_H,CRC_L,from_dress;
     if( g_RS485_Receive_Flag == 1 )
     {
            /* 判断起始码 ---------------------------------*/  
            if( DataBuff [date_lenth-1] != 0xaa)  { g_RS485_Receive_Flag = 0; return 1;}  //起始码错误      

            /* 判断CRC校验码 ------------------------------*/        
            CRC_H = DataBuff[1];  //转存CRC校验码
            CRC_L = DataBuff[0];
            VerifyCRC(DataBuff,RS485_DATA_LENTH);  
            if( DataBuff[1] != CRC_H ) { g_RS485_Receive_Flag = 0; return 2 ;}   //CRC校验错误
            if( DataBuff[0] != CRC_L ) { g_RS485_Receive_Flag = 0; return 2 ;} 
            
            /* 判断地址 ----------------------------------*/
            if( ( DataBuff[date_lenth - 2] != Local_Address )  && ( DataBuff[date_lenth - 2] != Address_All) ) { g_RS485_Receive_Flag = 0; return 3;}//非本机地址
            
            /* 判断发送方硬件类型 --------------------------*/
            from_dress = DataBuff[date_lenth - 3];
            if( from_dress < 0x10 )  gsa_Msg[from_dress].Hardware_Type = Type_HANDLE;      //手柄:0x00~0x0f
            else if( from_dress < 0x20 )  gsa_Msg[from_dress].Hardware_Type = Type_MASTER; //主板:0x10~0x1f
            else if( from_dress < 0x30 )  gsa_Msg[from_dress].Hardware_Type = Type_SENSOR; //传感器:0x20~0x2f
                
            /* 转存数据 -----------------------------------*/                       
            gsa_Msg[from_dress].Order = DataBuff[RS485_ORDER_BYTE]; //转存指令                 
            gsa_Msg[from_dress].a_Parameter[0] =  DataBuff[RS485_DATA_BYTE0]; //转存参数       
            gsa_Msg[from_dress].a_Parameter[1] =  DataBuff[RS485_DATA_BYTE1];                 
            gsa_Msg[from_dress].a_Parameter[2] =  DataBuff[RS485_DATA_BYTE2];                 
            gsa_Msg[from_dress].a_Parameter[3] =  DataBuff[RS485_DATA_BYTE3];                     
                
            /* 处理完毕 -----------------------------------*/
            gsa_Msg[from_dress].new_info = 1; //数据转存完毕,为新数据
            g_RS485_Receive_Flag = 0;   
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
static void VerifyCRC(unsigned char *DataBuff,unsigned char date_lenth)
{
    unsigned long int CRC_Value = 0;
    uchar CRC_Byte;
    
    for(CRC_Byte = 2; CRC_Byte < date_lenth ;CRC_Byte++)
    CRC_Value  =  ( CRC_Value + DataBuff[CRC_Byte]*CRC_Byte ) % CRC_CODE;           
    
    DataBuff[1] = CRC_Value/0xff;  
    DataBuff[0] = CRC_Value%0xff;   //传递参数
    
    if( DataBuff[1] == RS485_START ) DataBuff[1] --;  //避免出现 起始码
    if( DataBuff[0] == RS485_START ) DataBuff[0] --;
      
}


/**---------------------------------------------------------------------------- 
 * @Function_Name : RS485_AnalysisData()
 * @Description   : 数据分析函数
 * @Parameter     : void
 * @Return        ： void
 * @Programer     : WindRises（谢玉伸）
 * @Data          : 2015/12/19
 * @Explain       : None
------------------------------------------------------------------------------*/
void RS485_AnalysisData(void)
{
   uchar _Addr,_Flag = 0;
   uchar _PreData[RS485_DATA_LENTH];
   
    for( _Addr = Address_All; _Addr < DEVICE_NUMBER; _Addr++ ) //地址逐个查询
    if( gsa_Msg[_Addr].new_info == 1 ) //是否为新数据
    {
        //装载地址
        _PreData[RS485_LOCAL_ADRESS_BYTE] = Local_Address;  
        _PreData[RS485_DEST_ADRESS_BYTE] = _Addr; 
        /* 向本机进行操作 =============================================================*/
        /* 重置指令 ---------------------------------*/    
        if( gsa_Msg[_Addr].Order == Cmd_Reset ) 
        {
            gs_ComData.Current = Default_Current;   
            gs_ComData.Temp = Default_Temp;         
            gs_ComData.TiltingX = Default_TiltingX;     
            gs_ComData.TiltingY = Default_TiltingY;     
            gs_ComData.Weight = Default_Weight;         
        }
        
        /* 充磁指令 ---------------------------------*/   
        else if( gsa_Msg[_Addr].Order == Cmd_Magnet ) 
        {
            Relay_Control(1,1);
            
            
        }
        
        /* 退磁指令 ---------------------------------*/   
        else if( gsa_Msg[_Addr].Order == Cmd_Demagnet ) 
        {
            
        }
        
        
        /* 向本机写入数据 =============================================================*/
        /* 向本机写入电流 ---------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Write_Current ) 
        {
            gs_ComData.Current = gsa_Msg[_Addr].a_Parameter[0];      //数据低位  
            gs_ComData.Current += gsa_Msg[_Addr].a_Parameter[1]*256; //数据高位
            
            _PreData[RS485_ORDER_BYTE] = Cmd_State_Success;       //装载成功状态指令
            RS485_SendDate(_PreData,RS485_DATA_LENTH);          //返回成功状态   
        }                                                                                                     
           
        /* 向本机写入倾斜角 --------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Write_Tilting ) 
        {
            gs_ComData.TiltingX = gsa_Msg[_Addr].a_Parameter[0];
            gs_ComData.TiltingY = gsa_Msg[_Addr].a_Parameter[1];
            
            _PreData[RS485_ORDER_BYTE] = Cmd_State_Success;       //装载成功状态指令
            RS485_SendDate(_PreData,RS485_DATA_LENTH);          //返回成功状态   
        }
        
        /* 向本机写入质量 -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Write_Weight ) 
        {
            gs_ComData.Weight = gsa_Msg[_Addr].a_Parameter[0];
            gs_ComData.Weight += gsa_Msg[_Addr].a_Parameter[1]*256;
            
            _PreData[RS485_ORDER_BYTE] = Cmd_State_Success;       //装载成功状态指令
            RS485_SendDate(_PreData,RS485_DATA_LENTH);          //返回成功状态   
        }
        
        /* 向本机写入温度 -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Write_Temp ) 
        {
            gs_ComData.Temp = gsa_Msg[_Addr].a_Parameter[0];
            
            _PreData[RS485_ORDER_BYTE] = Cmd_State_Success;       //装载成功状态指令
            RS485_SendDate(_PreData,RS485_DATA_LENTH);          //返回成功状态   
        }
        
        /* 向本机读取数据 =============================================================*/
        /* 向本机读取电流 -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Read_Current ) 
        {
            _PreData[RS485_ORDER_BYTE] = Cmd_Write_Current;       //装载写入电流命令        
            _PreData[RS485_DATA_BYTE0] = gs_ComData.Current%256; //装载写入电流数据低位
            _PreData[RS485_DATA_BYTE1] = gs_ComData.Current/256; //装载写入电流数据高位
            _PreData[RS485_DATA_BYTE2] = RS485_VACANT;            //装载空闲值
            _PreData[RS485_DATA_BYTE3] = RS485_VACANT;     
            
            RS485_SendDate(_PreData,RS485_DATA_LENTH);          //发送数据
            
        }
        
        /* 向本机读取倾斜角 -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Read_Tilting ) 
        {
            _PreData[RS485_ORDER_BYTE] = Cmd_Write_Tilting;       //装载写入命令    
            _PreData[RS485_DATA_BYTE0] = gs_ComData.TiltingX;    //装载写入倾斜角X角    
            _PreData[RS485_DATA_BYTE1] = gs_ComData.TiltingY;    //装载写入倾斜角X角        
            _PreData[RS485_DATA_BYTE2] = RS485_VACANT;            
            _PreData[RS485_DATA_BYTE3] = RS485_VACANT;     
            RS485_SendDate(_PreData,RS485_DATA_LENTH);          //发送数据
        }
        
         /* 向本机读取质量 -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Read_Weight ) 
        {
            _PreData[RS485_ORDER_BYTE] = Cmd_Write_Weight;         //装载写入电流命令           
            _PreData[RS485_DATA_BYTE0] = gs_ComData.Weight % 256; //装载写入质量数据低位     
            _PreData[RS485_DATA_BYTE1] = gs_ComData.Weight / 256; //装载写入质量数据高位    
            _PreData[RS485_DATA_BYTE2] = RS485_VACANT;             //装载空闲值
            _PreData[RS485_DATA_BYTE3] = RS485_VACANT;     
            
            RS485_SendDate(_PreData,RS485_DATA_LENTH);          //发送数据
            
        }
        
         /* 向本机读取温度 -----------------------------------------*/
        else if( gsa_Msg[_Addr].Order == Cmd_Read_Temp ) 
        {
            _PreData[RS485_ORDER_BYTE] = Cmd_Write_Temp;          //装载写入温度命令
            _PreData[RS485_DATA_BYTE0] = gs_ComData.Temp;        //装载写入温度数据
            _PreData[RS485_DATA_BYTE1] = RS485_VACANT;            //装载空闲值
            _PreData[RS485_DATA_BYTE2] = RS485_VACANT;              
            _PreData[RS485_DATA_BYTE3] = RS485_VACANT;                  
                                                                
            RS485_SendDate(_PreData,RS485_DATA_LENTH);          //发送数据
        }
                     
    gsa_Msg[_Addr].new_info = 0; //新数据处理完毕    
    }   
    
           
}   

        
        
        
        
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/





