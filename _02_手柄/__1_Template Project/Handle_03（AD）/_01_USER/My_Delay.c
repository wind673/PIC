/*******************************(C) COPYRIGHT 2015 WindRises£®–ª”Ò…Ï£©*********************************/

/**============================================================================
* @File_Name   : My_Delay.c
* @Description : This file clude some delay functions
* @Date         : 2015/10/25
* @By           : WindRises£®–ª”Ò…Ï£©
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* Õ∑Œƒº˛∞¸∫¨ -----------------------------------------------------------------*/
#include "My_Delay.h"

/* ÀΩ”–∫Í∂®“Â -----------------------------------------------------------------*/

/* ÀΩ”–±‰¡ø…˘√˜ ---------------------------------------------------------------*/

/* ÀΩ”–£®æ≤Ã¨£©∫Ø ˝…˘√˜ --------------------------------------------------------*/
static void delay1ms(void);
static void delay1s(void);

/* »´æ÷∫Ø ˝±‡–¥ ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : delay_ms();	       
* @Description   : This function is using to delay (ms)
* @Parameter     : _ms(General parameters) msº∂—” ±
* @Return        : void
* @Programer     : WindRises£®–ª”Ò…Ï£©
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
* @Programer     : WindRises£®–ª”Ò…Ï£©
* @Data           : 2015/10/25
* @Explain       : This is a rough delay_function
------------------------------------------------------------------------------*/
void delay_s(unsigned int _s)
{
    while(_s--) delay1s();
}



/* ÀΩ”–£®æ≤Ã¨£©∫Ø ˝±‡–¥ -------------------------------------------------------*/
static void delay1ms(void)   //ŒÛ≤Ó -1us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=94;b>0;b--)
            for(a=2;a>0;a--);
}

static void delay1s(void)   //ŒÛ≤Ó -1us
{
    unsigned char a,b,c;
    for(c=205;c>0;c--)
        for(b=171;b>0;b--)
            for(a=8;a>0;a--);
  
}






/*******************************(C) COPYRIGHT 2015 WindRises£®–ª”Ò…Ï£©*********************************/
