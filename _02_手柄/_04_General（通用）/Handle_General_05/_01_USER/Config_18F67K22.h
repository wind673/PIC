/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Config_18F67K22.h
* @Description : 用来配置内部配置位
* @Date         : 2015/12/19（最后一次编写时间）
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 防止重调用 -----------------------------------------------------------------*/
#ifndef __CONFIG_F187K22_H
#define __CONFIG_F187K22_H
#include "My_Types.h"

/* 全局宏定义 -----------------------------------------------------------------*/
#define Local_Address Address_Handle_A   //本机地址：手柄A

/* 全局枚举定义 -----------------------------------------------------------------*/
/* 地址 ---------------------------------------------------*/
enum __Address
{
    Address_All = 0x00,          //全局广播
    Address_Master = 0x01,       //主控板
    Address_Sensor ,             //传感器  
    Address_SMPDP ,              //显示板    
    Address_Handle_A = 0x04,     //A号手柄   
    Address_Handle_B ,           //B号手柄
    Address_Handle_C ,           //C号手柄
    Address_Handle_D ,           //D号手柄
    
};

/* 操作指令 ------------------------------------------------*/
enum __Cmd   
{
    /* 操作指令 --------------------------*/
    Cmd_Reset = 0x00,            //重置所有数据到默认状态  
    Cmd_Magnet ,                 //充磁     
    Cmd_Demagnet ,               //退磁      
    
    /* 写入指令 --------------------------*/
    Cmd_Write_Current ,          //写入电流参数
    Cmd_Write_Tilting ,          //写入倾斜参数    
    Cmd_Write_Weight ,           //写入质量参数  
    Cmd_Write_Temp ,             //写入温度参数  
    
    /* 读取指令 --------------------------*/    
    Cmd_Read_Current ,           //读取电流参数  
    Cmd_Read_Tilting ,           //读取倾斜参数    
    Cmd_Read_Weight ,            //读取质量参数  
    Cmd_Read_Temp ,              //读取温度参数   
    
    /* 状态指令 --------------------------*/  
    Cmd_State_Success ,          //成功状态（用于返回操作结果）  
    Cmd_State_Failure ,          //成功状态（用于返回操作结果）  
    Cmd_State_Warning ,          //成功状态（用于返回操作结果）  
};    

/* 默认参数 ------------------------------------------------*/                              
enum __Default
{
    Default_Current = 0,       //电流默认值
    Default_TiltingX = 0,      //X轴倾斜角度默认值 
    Default_TiltingY = 0,      //Y轴倾斜角度默认值 
    Default_Weight = 0,        //质量默认值     
    Default_Temp = 0,          //温度值默认值 
    
}; 

/* 结构体定义 -----------------------------------------------------------------*/

/* 全局变量包含 ---------------------------------------------------------------*/

/* 全局变量声明 ---------------------------------------------------------------*/ 

/* 全局函数声明 ---------------------------------------------------------------*/ 

/* 头文件包含 -----------------------------------------------------------------*/
#include <xc.h>

// PIC18F67K22 Configuration Bit Settings

// 'C' source line config statements


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
/* 配置位 ---------------------------------------------------------------------*/
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

/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/