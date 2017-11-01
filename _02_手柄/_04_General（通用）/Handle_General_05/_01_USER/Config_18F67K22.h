/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : Config_18F67K22.h
* @Description : ���������ڲ�����λ
* @Date         : 2015/12/19�����һ�α�дʱ�䣩
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* ��ֹ�ص��� -----------------------------------------------------------------*/
#ifndef __CONFIG_F187K22_H
#define __CONFIG_F187K22_H
#include "My_Types.h"

/* ȫ�ֺ궨�� -----------------------------------------------------------------*/
#define Local_Address Address_Handle_A   //������ַ���ֱ�A

/* ȫ��ö�ٶ��� -----------------------------------------------------------------*/
/* ��ַ ---------------------------------------------------*/
enum __Address
{
    Address_All = 0x00,          //ȫ�ֹ㲥
    Address_Master = 0x01,       //���ذ�
    Address_Sensor ,             //������  
    Address_SMPDP ,              //��ʾ��    
    Address_Handle_A = 0x04,     //A���ֱ�   
    Address_Handle_B ,           //B���ֱ�
    Address_Handle_C ,           //C���ֱ�
    Address_Handle_D ,           //D���ֱ�
    
};

/* ����ָ�� ------------------------------------------------*/
enum __Cmd   
{
    /* ����ָ�� --------------------------*/
    Cmd_Reset = 0x00,            //�����������ݵ�Ĭ��״̬  
    Cmd_Magnet ,                 //���     
    Cmd_Demagnet ,               //�˴�      
    
    /* д��ָ�� --------------------------*/
    Cmd_Write_Current ,          //д���������
    Cmd_Write_Tilting ,          //д����б����    
    Cmd_Write_Weight ,           //д����������  
    Cmd_Write_Temp ,             //д���¶Ȳ���  
    
    /* ��ȡָ�� --------------------------*/    
    Cmd_Read_Current ,           //��ȡ��������  
    Cmd_Read_Tilting ,           //��ȡ��б����    
    Cmd_Read_Weight ,            //��ȡ��������  
    Cmd_Read_Temp ,              //��ȡ�¶Ȳ���   
    
    /* ״ָ̬�� --------------------------*/  
    Cmd_State_Success ,          //�ɹ�״̬�����ڷ��ز��������  
    Cmd_State_Failure ,          //�ɹ�״̬�����ڷ��ز��������  
    Cmd_State_Warning ,          //�ɹ�״̬�����ڷ��ز��������  
};    

/* Ĭ�ϲ��� ------------------------------------------------*/                              
enum __Default
{
    Default_Current = 0,       //����Ĭ��ֵ
    Default_TiltingX = 0,      //X����б�Ƕ�Ĭ��ֵ 
    Default_TiltingY = 0,      //Y����б�Ƕ�Ĭ��ֵ 
    Default_Weight = 0,        //����Ĭ��ֵ     
    Default_Temp = 0,          //�¶�ֵĬ��ֵ 
    
}; 

/* �ṹ�嶨�� -----------------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/

/* ȫ�ֱ������� ---------------------------------------------------------------*/ 

/* ȫ�ֺ������� ---------------------------------------------------------------*/ 

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include <xc.h>

// PIC18F67K22 Configuration Bit Settings

// 'C' source line config statements


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
/* ����λ ---------------------------------------------------------------------*/
// CONFIG1L
#pragma config RETEN = ON       // VREG Sleep Enable bit (Enabled)
#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
#pragma config SOSCSEL = DIG   // SOSC Power Selection and mode Configuration bits (High Power SOSC circuit selected)
#pragma config XINST = OFF       // Extended Instruction Set (Enabled)

// CONFIG1H
#pragma config FOSC = HS1    // Oscillator (Internal RC oscillator)
#pragma config PLLCFG = OFF     // PLL x4 Enable bit (Disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power Up Timer (Disabled)
#pragma config BOREN = SBORDIS  // Brown Out Detect (Enabled in hardware, SBOREN disabled)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (1.8V)
#pragma config BORPWR = ZPBORMV // BORMV Power level (ZPBORMV instead of BORMV is selected)

// CONFIG2H
#pragma config WDTEN = OFF  // Watchdog Timer (WDT enabled in hardware; SWDTEN bit disabled)
#pragma config WDTPS = 1048576  // Watchdog Postscaler (1:1048576)

// CONFIG3L
#pragma config RTCOSC = SOSCREF // RTCC Clock Select (RTCC uses SOSC)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 Mux (RC1)
#pragma config MSSPMSK = MSK7   // MSSP address masking (7 Bit address masking mode)
#pragma config MCLRE = ON       // Master Clear Enable (MCLR Enabled, RG5 Disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Overflow Reset (Enabled)
#pragma config BBSIZ = BB2K     // Boot Block Size (2K word Boot Block size)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protect 00800-03FFF (Disabled)
#pragma config CP1 = OFF        // Code Protect 04000-07FFF (Disabled)
#pragma config CP2 = OFF        // Code Protect 08000-0BFFF (Disabled)
#pragma config CP3 = OFF        // Code Protect 0C000-0FFFF (Disabled)
#pragma config CP4 = OFF        // Code Protect 10000-13FFF (Disabled)
#pragma config CP5 = OFF        // Code Protect 14000-17FFF (Disabled)
#pragma config CP6 = OFF        // Code Protect 18000-1BFFF (Disabled)
#pragma config CP7 = OFF        // Code Protect 1C000-1FFFF (Disabled)

// CONFIG5H
#pragma config CPB = OFF        // Code Protect Boot (Disabled)
#pragma config CPD = OFF        // Data EE Read Protect (Disabled)

// CONFIG6L
#pragma config WRT0 = OFF       // Table Write Protect 00800-03FFF (Disabled)
#pragma config WRT1 = OFF       // Table Write Protect 04000-07FFF (Disabled)
#pragma config WRT2 = OFF       // Table Write Protect 08000-0BFFF (Disabled)
#pragma config WRT3 = OFF       // Table Write Protect 0C000-0FFFF (Disabled)
#pragma config WRT4 = OFF       // Table Write Protect 10000-13FFF (Disabled)
#pragma config WRT5 = OFF       // Table Write Protect 14000-17FFF (Disabled)
#pragma config WRT6 = OFF       // Table Write Protect 18000-1BFFF (Disabled)
#pragma config WRT7 = OFF       // Table Write Protect 1C000-1FFFF (Disabled)

// CONFIG6H
#pragma config WRTC = OFF       // Config. Write Protect (Disabled)
#pragma config WRTB = OFF       // Table Write Protect Boot (Disabled)
#pragma config WRTD = OFF       // Data EE Write Protect (Disabled)

// CONFIG7L
#pragma config EBRT0 = OFF      // Table Read Protect 00800-03FFF (Disabled)
#pragma config EBRT1 = OFF      // Table Read Protect 04000-07FFF (Disabled)
#pragma config EBRT2 = OFF      // Table Read Protect 08000-0BFFF (Disabled)
#pragma config EBRT3 = OFF      // Table Read Protect 0C000-0FFFF (Disabled)
#pragma config EBRT4 = OFF      // Table Read Protect 10000-13FFF (Disabled)
#pragma config EBRT5 = OFF      // Table Read Protect 14000-17FFF (Disabled)
#pragma config EBRT6 = OFF      // Table Read Protect 18000-1BFFF (Disabled)
#pragma config EBRT7 = OFF      // Table Read Protect 1C000-1FFFF (Disabled)

// CONFIG7H
#pragma config EBRTB = OFF      // Table Read Protect Boot (Disabled)




#endif

/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/