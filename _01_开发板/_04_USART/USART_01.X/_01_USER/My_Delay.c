/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : My_Delay.c
* @Description : This file clude some delay functions
* @Date         : 2015/10/25
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "My_Delay.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/
static void delay1ms(void);
static void delay1s(void);

/* ȫ�ֺ�����д ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : delay_ms();	       
* @Description   : This function is using to delay (ms)
* @Parameter     : _ms(General parameters)
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/10/25
* @Explain       : This is a rough delay_function
------------------------------------------------------------------------------*/
void delay_ms(unsigned int _ms)
{
    while(_ms--) delay1ms();
}


/**----------------------------------------------------------------------------
* @Function_Name : delay_s();	       
* @Description   : This function is using to delay (s)
* @Parameter     : _ms(General parameters)
* @Return         : void
* @Programer     : WindRises��л���죩
* @Data           : 2015/10/25
* @Explain       : This is a rough delay_function
------------------------------------------------------------------------------*/
void delay_s(unsigned int _s)
{
    while(_s--) delay1s();
}



/* ˽�У���̬��������д -------------------------------------------------------*/
static void delay1ms(void)   //��� -1us
{
    unsigned char a,b;
    for(b=16;b>0;b--)
        for(a=40;a>0;a--);

}

static void delay1s(void)   //��� -1us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=23;b>0;b--)
            for(a=172;a>0;a--);
}






/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/
