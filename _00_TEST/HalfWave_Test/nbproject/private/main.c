/**********************************************************************************************
 *   文 件 名：main.c
 *
 *   调试平台：PIC18FXX 开发平台
 *
 *   作    者：唐 江
 *
 *   日    期：2013.9.4
 **********************************************************************************************/
 
/* 包含 --------------------------------------------------------------------------------------*/
#include "main.h"

/* 私有宏 ------------------------------------------------------------------------------------*/

/* 私有变量 ----------------------------------------------------------------------------------*/

/* 私有结构体 --------------------------------------------------------------------------------*/

/* 私有函数声明 ------------------------------------------------------------------------------*/

/* 私有函数模型 ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *名    称：void main(void) 
 *
 *参    数：无
 *
 *返 回 值：无
 *
 *描    述：主函数
 *********************************************************************************************/
int main(void) 
{
    int vol;                
    GPIO_Init();          
    RS485_halInit();   
    Parameter_Init();          
    ADC_Init();         
    while(1)
    {
        vol = ADC_ElecGet();
    }
}
/* 文件结束 ---------------------------------------------------------------------------------*/









