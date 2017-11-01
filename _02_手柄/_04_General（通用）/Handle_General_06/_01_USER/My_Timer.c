/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : My_Timer.c
* @Description : 定时器源文件
* @Date         : 2015/10/29
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include "My_Timer.h"
#include "GPIO.h"
#include "My_ADC.h"
#include "My_USART.h"
#include "Run.h"
#include "My_Delay.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/
long unsigned  int g_Timer_Cyc = 0;
        
/* 全局变量声明 ---------------------------------------------------------------*/

/* 全局函数编写 ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : Timer0_Init()     
* @Description   : 定时器初始化
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
void Timer0_Init(void)
{ 
   T08BIT = 0;      //16 位模式控制位 
   T0CS = 0;        //内部时钟 （0: F OSC/4 = 2M ） 
   T0SE = 0;        //时钟源边沿选择位 （0:上升沿递增）
   PSA = 0;         //预分配 （0: 打开预分配）
   T0PS2 = 1; 
   T0PS1 = 1;   
   T0PS0 = 1;       /*                     
                    T0PS<2:0> ：Timer0 预分频值选择位
                     *                       
                    111 = 1:256 预分频值         慢
                    110 = 1:128 预分频值 
                    101 = 1:64 预分频值   
                    100 = 1:32 预分频值  
                    011 = 1:16 预分频值  
                    010 = 1:8 预分频值   
                    001 = 1:4 预分频值
                    000 = 1:2 预分频值             快
                    例如 111 ，时钟速率是原来的1/256
                     */     
                    
   SetTimer0(1); //设置溢出值 
   TMR0ON = 1;      //使能 Timer0
   TMR0IE = 1;      // 允许 TMR0 溢出中断
   IPEN = 0;GIE = 1;//允许所有未屏蔽的中断
}


/**----------------------------------------------------------------------------
* @Function_Name : SetTimer0(uint _tmr)      
* @Description   : 设置定时器装载 
* @Parameter     : _tmr（uint）
* @Return        : void 
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/11/2 
* @Explain       : 0~0xffff(16位的情况下)
------------------------------------------------------------------------------*/
void SetTimer0( uint _tmr ) 
{
    if(_tmr > 0xffff) _tmr = 0xffff;
    _tmr=0xffff-_tmr;//PIC的累加方式是向上累加的
    TMR0H = _tmr/256;
    TMR0L = _tmr%256;
    TMR0IF = 0; //清除标志位 
}


/**----------------------------------------------------------------------------
* @Function_Name : interrupt Sys_Cyc(void) 
* @Description   : 中断服务函数 
* @Parameter     : void
* @Return        : void 
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/11/2
* @Explain       : None
------------------------------------------------------------------------------*/
void interrupt Sys_Cyc(void) 
{
    static unsigned char _overturn_LED = 0;  //LED灯翻转
    static char _Byte; //RS485接收位
    static char _flag = 0; 
    unsigned char _temp;
    
   /* TIMER0  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/     
   if(TMR0IF)
   {  
        g_Timer_Cyc = (g_Timer_Cyc+1) % 4294967296; //全局定时器
        SetTimer0(78); //重设溢出值 78 * 128us = 10ms 
        
        /* 指示灯闪烁 ------------------------------*/  
        if( g_Timer_Cyc%30 == 0 )  //运行指示灯闪烁
        {
           _overturn_LED = ~_overturn_LED;
           if(_overturn_LED)  LED3_ON(); 
           else               LED3_OFF();
        }
        
        /* 1KHZ脉冲输出 ----------------------------*/ 
        if( gs_Switch._1Khz ) //1KHZ脉冲输出
         Pulse_1Khz();        
        
        /* 按键扫描 --------------------------------*/    
        Key_ScanFSM();//10ms检测一次按键              
   }
    
    /* USART2  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/       
    if( RC2IF )
    {
        _temp = RCREG2; 
        if( g_RS485_Receive_Flag == 0 ) //接收标志已复位
        {
            if( _temp == RS485_START ) //起始码
            {
                 _Byte = RS485_DATA_LENTH ;          
                 _flag = 0;            
             }   
                    
            if ( _flag == 0 )
            {
                 _Byte -- ; 
                 ga_RS485_ReceiveBuff[ _Byte ] = _temp;  //接收数据   
             }
                
             if( _Byte == 0 )  
             {
                 g_RS485_Receive_Flag = 1 ;  //接收1组数据完毕
                 _flag = 1;
             }
        }
    }
        
}


/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/



