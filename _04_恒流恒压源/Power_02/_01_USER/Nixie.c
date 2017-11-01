/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
/**============================================================================
* @File_Name   : Nixie.c
* @Description : None
* @Date         : 2016/2/20
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/
/* 头文件包含 -----------------------------------------------------------------*/
#include "Nixie.h"               
#include "My_Delay.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量声明 ---------------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/
unsigned char Nix_Flash;

/* 全局变量声明 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*

/* 全局函数编写 ---------------------------------------------------------------*/

//共阴级数码管段码
const unsigned char LED_Number[10] = {~0xc0,~0xf9,~0xa4,~0xb0,~0x99,~0x92,~0x82,~0xf8,~0x80,~0x90};

void Nixie_Init(void)
{
    TRISC = 0; //将C总线上的IO口全部配置为输出 
    TRISAbits.TRISA4 = 0; 
    TRISAbits.TRISA5 = 0;       
    ANSEL4 = 0;
    
    PORTC = 0xff;   
    /*段选 ---------------------------------*/
    NIX_S2();
    
}

void Nixie_ShowBit(unsigned char _bit,unsigned char _num)
{
    if(_bit) NIX_S2();  //1 各位
    else   NIX_S1();    //0 小数位
    
    PORTC = LED_Number[_num];
}


void Nixie_ShowNum(unsigned char _num)
{
    static unsigned char _t = 0;
       
    _t = ~_t; 
    if(_t)
    {
        NIX_S1();  
        PORTC = LED_Number[_num/10];   
    }
    else
    {
        NIX_S2();  
        PORTC = LED_Number[_num%10];  
    }
     
}