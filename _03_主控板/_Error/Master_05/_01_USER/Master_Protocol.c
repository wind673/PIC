/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Master_Protocol.c
* @Description : 手柄通讯协议源文件
* @Date         : 2015/12/20
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : 从机，只需要按主机的命令办事，不需要主动发送数据
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/       
#include <pic18f67k22.h>
#include "Master_Protocol.h"
#include "usart.h"
#include <math.h>
#include "Run.h"
#include "Config_18F67K22.h"
#include "My_USART.h"
#include "Run.h"     

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/
  
/* 私有（静态）函数声明 --------------------------------------------------------*/
static void Cmd_Inquiry_Fun(uchar _Addr);

/* 全局变量定义 ---------------------------------------------------------------*/
unsigned char ga_RS485_SendBuff[RS485_DATA_LENTH] = {0};      //RS485发送数据缓存区         
unsigned char ga_RS485_ReceiveBuff[RS485_DATA_LENTH] = {0};   //RS485接收数据缓存区 
unsigned char g_RS485_Byte = 0;                               //RS485字节位             
unsigned char g_RS485_Receive_Flag = 0; 

/* 私有函数编写 ---------------------------------------------------------------*/

/**---------------------------------------------------------------------------- 
 * @Function_Name : Cmd_Inquiry_Fun()
 * @Description   : 查询命令
 * @Parameter     : void
 * @Return        ： void
 * @Programer     : WindRises（谢玉伸）
 * @Data          : 2015/12/19
 * @Explain       : None
------------------------------------------------------------------------------*/
static void Cmd_Inquiry_Fun(uchar _Addr)
{
    uchar _PreData[RS485_DATA_LENTH]; //准备发送的数据
    /* 装载地址 -----------------------------------*/
    _PreData[RS485_LOCAL_ADRESS_BYTE] = Local_Address;                              
    _PreData[RS485_DEST_ADRESS_BYTE] = _Addr;                                 
     
    /* 装载数据 -----------------------------------*/
    _PreData[RS485_DATA_BYTE0] = RS485_VACANT; //装载写入电流数据低位
    _PreData[RS485_DATA_BYTE1] = RS485_VACANT; //装载写入电流数据高位
    _PreData[RS485_DATA_BYTE2] = RS485_VACANT; //装载空闲值
    _PreData[RS485_DATA_BYTE3] = RS485_VACANT;     
    
    /* 装载命令 -----------------------------------*/
    _PreData[RS485_ORDER_BYTE] = Cmd_Inquiry;       //装载查询命令   
    
    RS485_SendDate(_PreData,RS485_DATA_LENTH);    //发送数据
        
}

/* 全局函数编写 ---------------------------------------------------------------*/

/**---------------------------------------------------------------------------- 
 * @Function_Name : RS485_Inquiry()
 * @Description   : 循环查询函数
 * @Parameter     : void
 * @Return        ： void
 * @Programer     : WindRises（谢玉伸）
 * @Data          : 2015/12/19
 * @Explain       : 主机进行循环查询
------------------------------------------------------------------------------*/
void RS485_Inquiry(void)
{   
    static unsigned char  _NowAddr = Address_Handle_A;
    uchar _PreData[RS485_DATA_LENTH]; //准备发送的数据
   
    if( gs_Switch.Inquiry == 1 )  //Timer1定时开启 Inquiry
    { //定时查询
      
        Cmd_Inquiry_Fun(_NowAddr);   //发送查询指令                 
        _NowAddr ++;  
        if( _NowAddr == RS485_DATA_LENTH ) _NowAddr = Address_Handle_A;  //循环查询
        
        gs_Switch.Inquiry = 0;   //查询完毕
    }   
    
}

    
/**----------------------------------------------------------------------------
 * @Function_Name : RS485_RecogniseMessage( )
 * @Description   : RS485消息识别
 * @Parameter     : DataBuff[]：RS485所接收的一帧数据 
 *                    date_lenth：一帧数据的长度
 * @Return        : char
 * @Programer     : WindRises（谢玉伸）
 * @Data          : 2015/12/13
 * @Explain       : 接收成功返回1  否则返回0
------------------------------------------------------------------------------*/
unsigned char  RS485_RecogniseMessage( unsigned char DataBuff[] ,unsigned char date_lenth )
{
     unsigned char CRC_H,CRC_L,from_dress;
     if( gs_Switch.Receive == 1 )  //只有接收完一组数据才会更新数据
     {
            /* 判断起始码 ---------------------------------*/  
            if( DataBuff [date_lenth-1] != 0xaa)  {  gs_Switch.Receive = 0; return 1;}  //起始码错误      

            /* 判断CRC校验码 ------------------------------*/        
            CRC_H = DataBuff[1];  //转存CRC校验码  
            CRC_L = DataBuff[0];       
            VerifyCRC(DataBuff,RS485_DATA_LENTH);  
            if( DataBuff[1] != CRC_H ) {  gs_Switch.Receive = 0; return 2 ;}   //CRC校验错误
            if( DataBuff[0] != CRC_L ) {  gs_Switch.Receive = 0; return 2 ;} 
            
            /* 判断地址 ----------------------------------*/
            if( ( DataBuff[date_lenth - 2] != Local_Address )  && ( DataBuff[date_lenth - 2] != Address_All) ) {  gs_Switch.Receive = 0; return 3;}//非本机地址
            
          
            
            /* 处理完毕 -----------------------------------*/
            gsa_Msg[from_dress].new_info = 1; //数据转存完毕,为新数据
            gs_Switch.Receive = 0;   
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
 void VerifyCRC(unsigned char *DataBuff,unsigned char date_lenth)
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
   uchar _Addr,temp;
   uchar _PreData[RS485_DATA_LENTH];
   
 
                     
    gsa_Msg[_Addr].new_info = 0; //新数据处理完毕    
    
}
    
           
   
    
        
        
/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/





