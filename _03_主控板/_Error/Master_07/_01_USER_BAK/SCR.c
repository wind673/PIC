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

/* 私有宏定义 -----------------------------------------------------------------*/
#define PULSE_CNT 8  //发送1Khz脉冲的个数 

/* 私有变量定义 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/
static void Delay_1Khz(void);   //误差 -1us

/* 全局变量定义 ---------------------------------------------------------------*/
  
/* 全局函数编写 ---------------------------------------------------------------*/

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
* @Function_Name : Delay_1Khz()	       
* @Description   : 延时标准1ms
* @Parameter     : _ms(General parameters)
* @Return         : void
* @Programer     : WindRises（谢玉伸）
* @Data           : 2015/12/15
* @Explain       : None
------------------------------------------------------------------------------*/
static void Delay_1Khz(void)   //误差 -1us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
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
void Pulse_1Khz(unsigned char _QD)
{
    unsigned char _pulse = PULSE_CNT;  //PULSE_Number 个脉冲
    static unsigned char _overturn_1Khz = 0;
    
    /* 向QD1端口发送1Khz脉冲 -----------------------*/
    if(_QD == 1)
    while( _pulse-- ) 
    {
        _overturn_1Khz =~ _overturn_1Khz;
        if(_overturn_1Khz) _1Khz_Out1_ON(); 
        else _1Khz_Out1_ON();
        Delay_1Khz();
    } 
    
    /* 向QD2端口发送1Khz脉冲 -----------------------*/
    if(_QD == 2)
    while( _pulse-- ) 
    {
        _overturn_1Khz =~ _overturn_1Khz;
        if(_overturn_1Khz) _1Khz_Out2_ON(); 
        else _1Khz_Out2_ON();
        Delay_1Khz();
    
    }
    
}




/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

