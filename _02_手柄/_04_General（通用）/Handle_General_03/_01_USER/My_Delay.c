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
#include "GPIO.h"
#include "Run.h"


/* ˽�к궨�� -----------------------------------------------------------------*/
#define PULSE_CNT 10  //����1Khz����ĸ��� 


/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/
static void delay1ms(void);
static void delay1s(void);

/* ȫ�ֺ�����д ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : delay_ms();	       
* @Description   : This function is using to delay (ms)
* @Parameter     : _ms(General parameters) ms����ʱ
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
* @Function_Name : delay_s()	       
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

/**----------------------------------------------------------------------------
* @Function_Name : Delay_1Khz()	       
* @Description   : ��ʱ��׼1ms
* @Parameter     : _ms(General parameters)
* @Return         : void
* @Programer     : WindRises��л���죩
* @Data           : 2015/12/15
* @Explain       : 
------------------------------------------------------------------------------*/
void Delay_1Khz(void)   //��� -1us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=32;b>0;b--)
            for(a=2;a>0;a--);
}

/**----------------------------------------------------------------------------
* @Function_Name : Pulse_1Khz(void)       
* @Description   : ��ʱ��׼1ms
* @Parameter     : _ms(General parameters)
* @Return         : void
* @Programer     : WindRises��л���죩
* @Data           : 2015/12/15
* @Explain       : 
------------------------------------------------------------------------------*/
void Pulse_1Khz(void)
{
    unsigned char _pulse = PULSE_CNT;  //PULSE_Number ������
    static unsigned char _overturn_1Khz = 0;
    
   while( _pulse-- ) 
   {
                _overturn_1Khz =~ _overturn_1Khz;
                if(_overturn_1Khz) _1Khz_Out_ON(); 
                else _1Khz_Out_OFF();
                Delay_1Khz();
    } 
    
}





/* ˽�У���̬��������д -------------------------------------------------------*/
static void delay1ms(void)   //��� -1us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=94;b>0;b--)
            for(a=2;a>0;a--);
}

static void delay1s(void)   //��� -1us
{
    unsigned char a,b,c;
    for(c=205;c>0;c--)
        for(b=171;b>0;b--)
            for(a=8;a>0;a--);
  
}





/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/
