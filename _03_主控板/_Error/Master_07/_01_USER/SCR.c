/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : SCR.c
* @Description : 可控硅驱动程序源文件
* @Date         : 2015/12/19
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/                  
#include <pic18f67k22.h>                //PIC官方函数库          
#include "My_Types.h"                   //自定义的习惯写法定义     
#include "SCR.h"                        //继电器            
#include "Run.h"                        //主要运行函数
#include "Relay.h"                      //继电器
#include "My_Delay.h"                   //延时函数

/* 私有宏定义 -----------------------------------------------------------------*/
#define PULSE_CNT 8  //发送1Khz脉冲的个数 

/* 私有变量定义 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/
void Delay_1Khz(void);   //误差 -1us

/* 全局变量定义 ---------------------------------------------------------------*/
  
/* 全局函数编写 ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : SCR_Magnet()     
* @Description   : 充磁函数
* @Parameter     : _ch:充磁通道
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/19
* @Explain       : None
------------------------------------------------------------------------------*/
void SCR_Magnet(unsigned char _ch)
{
//    暂时是模拟充磁
    Relay_Control(_ch,1);                   
    delay_ms(100);
    Relay_Control(_ch,0);     
    gs_Switch.a_Magnet[_ch] = 0;
}

/**----------------------------------------------------------------------------
* @Function_Name : SCR_Demagnet()     
* @Description   : 退磁函数
* @Parameter     : _ch:退磁通道
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/19
* @Explain       : None
------------------------------------------------------------------------------*/
void SCR_Demagnet(unsigned char _ch)
{
    //暂时是模拟退磁
    Relay_Control(_ch,1);                   
    delay_ms(100);
    Relay_Control(_ch,0);
    gs_Switch.a_Demagnet[_ch] = 0;
}

/**----------------------------------------------------------------------------
* @Function_Name : SCR_Init()     
* @Description   : 继电器初始化
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/19
* @Explain       : None
------------------------------------------------------------------------------*/
void SCR_Init(void)
{
     /*初始化可控硅的IO口 ----------------------*/
    RB1 = 0;       
    RB0 = 0;
    
    /*配置可控硅的IO口 -----------------------*/
    TRISB1 = 0;  //QD1 :可控硅的反向导通
    TRISB0 = 0;  //QD2 :可控硅的正向导通
    
    /*配置过零检测IO口 -----------------------*/
    TRISB2 = 1;  //过零检测IO口：输入模式
}


/**----------------------------------------------------------------------------
* @Function_Name : Delay_3Khz()	       
* @Description   : 延时标准1.5ms
* @Parameter     : coid
* @Return         : void
* @Programer     : WindRises（谢玉伸）
* @Data           : 2015/12/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Delay_3Khz(void)   //误差 -1us
{
    unsigned char a,b,c;
    for(c=3;c>0;c--)
        for(b=32;b>0;b--)
            for(a=2;a>0;a--);
}

/**----------------------------------------------------------------------------
* @Function_Name : Pulse_1Khz()       
* @Description   : 发送1Khz脉冲
* @Parameter     : _QD：发送的IO口
* @Return         : void
* @Programer     : WindRises（谢玉伸）
* @Data           : 2015/12/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Pulse_3Khz(unsigned char _QD)
{
    unsigned char _pulse = PULSE_CNT;  //PULSE_Number 个脉冲
    static unsigned char _overturn_3Khz = 0;
    
    /* 向QD1端口发送3Khz脉冲 -----------------------*/
    if(_QD == 1)
    while( _pulse-- ) 
    {
        _overturn_3Khz =~ _overturn_3Khz;
        if(_overturn_3Khz) _3Khz_Out1_ON(); 
        else _3Khz_Out1_OFF();
        Delay_3Khz();
    } 
    
    /* 向QD2端口发送3Khz脉冲 -----------------------*/
    if(_QD == 2)
    while( _pulse-- ) 
    {
        _overturn_3Khz =~ _overturn_3Khz;
        if(_overturn_3Khz) _3Khz_Out2_ON(); 
        else _3Khz_Out2_OFF();
        Delay_3Khz();
    
    }
    
}




/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

