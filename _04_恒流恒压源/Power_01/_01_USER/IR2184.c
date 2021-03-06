/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
/**============================================================================
* @File_Name   : IR2184.c
* @Description : None
* @Date         : 2016/2/20
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* 头文件包含 -----------------------------------------------------------------*/
#include "IR2184.h"               

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/

/* 全局变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*

/* 全局函数编写 ---------------------------------------------------------------*/

 
void IR2184_Init(void)
{
    TRISDbits.TRISD2 = 0;  //IN1
    TRISDbits.TRISD3 = 0;  //SD1
    
    TRISEbits.TRISE5 = 0;  //IN2 ****
    TRISEbits.TRISE6 = 0;  //SD2
     
    IR2184_OFF_1();     
    IR2184_OFF_2();    
    
}
  

