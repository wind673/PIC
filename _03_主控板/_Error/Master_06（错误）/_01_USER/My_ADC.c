/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : My_ADC.c
* @Description : ADC采集功能实现源文件
* @Date         : 2015/12/5
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include "My_ADC.h"
#include "adc.h"
#include "Master_Protocol.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/
 volatile float gf_ADC6_Buff = 0;  
 
/* 全局函数编写 ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : ADC6_Init()     
* @Description   : ADC6初始化程序
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/5
* @Explain       : None
------------------------------------------------------------------------------*/
void ADC6_Init()
{  
    
    OpenADC(ADC_RIGHT_JUST &
            ADC_2_TAD &
            ADC_FOSC_2 
            ,
            ADC_CH6
            ,
            ADC_TRIG_CCP2 &
            ADC_REF_VDD_INT_VREF_4 &   //参考电压：电源电压（需要软件偏正）
            ADC_REF_VDD_VSS &          //负参考电压选择
            ADC_NEG_CH0               //模拟负通道选择位（一般选择通道0--AVss）
            );
  
    ADC_INT_DISABLE();                 //打开ADC中断
//    ConvertADC();
//    while(BusyADC());
//    ReadADC();
}   

/**----------------------------------------------------------------------------
* @Function_Name : GetADC6()     
* @Description   : ADC6采集并转换
* @Parameter     : float
* @Return        : (float) AD0_Buff: ADC6的模拟电压值
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/8
* @Explain       : None
------------------------------------------------------------------------------*/
void GetADC6()  
{
    ConvertADC();                  
    while(BusyADC());      
    gf_ADC6_Buff =(unsigned int)ReadADC()*4.096f/4095.0f;   
//    gs_Switch.ADC6 = 0;   
    
}



/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

