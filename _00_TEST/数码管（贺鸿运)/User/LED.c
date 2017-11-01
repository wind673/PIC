/*
 * File:   LED.c
 * Author: SuiFeng
 *
 * Created on 2015年12月2日, 下午1:29
 */


#include <xc.h>
#include "LED.h"

void Init_LED(void)
{
    TRISE5 = 0;
    TRISE6 = 0;
    TRISE7 = 0;
    
    LED_1_IO = LIGHT;
    LED_2_IO = LIGHT;
    LED_3_IO = LIGHT;
}

void Lighten_LED(unsigned char LED_Num)
{
    if((LED_Num & LED_1) != 0)
        LED_1_IO = LIGHT;

    if((LED_Num & LED_2) != 0)
        LED_2_IO = LIGHT;
    
    if((LED_Num & LED_3) != 0)
        LED_3_IO = LIGHT;
}

void Quench_LED(unsigned char LED_Num)
{
    if((LED_Num & LED_1) != 0)
        LED_1_IO = QUENCH;

    if((LED_Num & LED_2) != 0)
        LED_2_IO = QUENCH;
    
    if((LED_Num & LED_3) != 0)
        LED_3_IO = QUENCH;
}

