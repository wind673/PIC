/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : GPIO_Config.c
* @Description : None
* @Date         : 2015/10/29
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "GPIO_Config.h"
#include "My_Types.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/

/* ȫ�ֺ�����д ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : GPIO_Config()      
* @Description   : GPIO�����ú���
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
void GPIO_Config()
{
    TRISE=0x00;//��E��ȫ�����ó����
}

/**----------------------------------------------------------------------------
* @Function_Name : LED_Control()      
* @Description   :LED���ƺ���
* @Parameter     : _Dx��LED��ţ�, _switch������״̬��1�� 0�أ�  
* @Return        : _switch(LED���ڵ�״̬)  
* @Programer     : WindRises��л���죩
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned char  LED_Control(unsigned char _Dx,unsigned char _switch)
{
    switch (_Dx)
    {
        case 1 : if(_switch) PORTEbits.RE2=0; else PORTEbits.RE2=1; break;
        case 2 : if(_switch) PORTEbits.RE3=0; else PORTEbits.RE3=1; break;
        case 3 : if(_switch) PORTEbits.RE4=0; else PORTEbits.RE4=1; break;
        case 4 : if(_switch) PORTEbits.RE5=0; else PORTEbits.RE5=1; break;
    }
    
    return _switch;
}


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/


