/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : GPIO_Config.c
* @Description : None
* @Date         : 2015/10/29
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "GPIO.h"
#include "My_Types.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/
uchar LED_switch = 0;

/* 全局函数编写 ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : GPIO_Config()      
* @Description   : GPIO的配置函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
void GPIO_Config()
{
    
    TRISE &= 0xc3;//将E2,3,4,5配置成输出(写入0用 & )
    TRISF = 0x01;//将F0配置成输出(写入0用 & )
   
}

/**----------------------------------------------------------------------------
* @Function_Name : LED_Control()      
* @Description   :LED控制函数
* @Parameter     : _LEDx（LED序号）, _switch（开关状态：1开 0关）  
* @Return        : _switch(LED现在的状态)  
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned char  LED_Control(unsigned char _LEDx,unsigned char _switch)
{
    switch (_LEDx)
    {
        case 1 : if(_switch) PORTEbits.RE2=0; else PORTEbits.RE2=1; break;     
        case 2 : if(_switch) PORTEbits.RE3=0; else PORTEbits.RE3=1; break;     
        case 3 : if(_switch) PORTEbits.RE4=0; else PORTEbits.RE4=1; break;     
        case 4 : if(_switch) PORTEbits.RE5=0; else PORTEbits.RE5=1; break;     
    }                                                                                      
    return _switch;
}


/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/











