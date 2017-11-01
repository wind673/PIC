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

/* 私有宏定义 -----------------------------------------------------------------*/
#define PULSE_Number 10
/* 私有变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/
unsigned long int Timer_Cyc = 0;
__Switch_Def Handle_01_Switch = {0,0};
        
/* 全局变量声明 ---------------------------------------------------------------*/

/* 全局函数编写 ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : My_Timer_Init()     
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
    static unsigned char _overturn_1Khz = 0;  
    unsigned char _pulse = PULSE_Number;  //PULSE_Number 个脉冲
    
   /*---------------- TIMER0 ----------------*/ 
   if(TMR0IF && TMR0IE)
   {  
        Timer_Cyc = (Timer_Cyc+1) % 100000000; //全局定时器
        
        if( Handle_01_Switch._1Khz ) //1KHZ脉冲输出
        {
            while( _pulse-- ) 
            {
                _overturn_1Khz =~ _overturn_1Khz;
                if(_overturn_1Khz) _1Khz_Out_ON; else _1Khz_Out_OFF;
                Delay_1Khz();
            }
        }
        
       Key_FSM_Scan();//10ms检测一次按键
       SetTimer0(78); //重设溢出值 78 * 128us = 10ms 
   }
    
}


/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/



