/*
 * File:   main.c
 * Author: SuiFeng
 *
 * Created on 2015年12月2日, 下午1:26
 */
    
    
#include <xc.h>
#include "main.h"
#include "LED.h"
#include "Key.h"
#include "TM1640.h"

void main(void)
{
    unsigned char NUM = 0x0f;
    int i;
    Init_System();

//    TM1640_Show_Numbers(7664);
    TM1640_Writer_Dates(0, 0x3F);
    TM1640_Writer_Dates(1, 0x5B);
    TM1640_Writer_Dates(2, 0x4F);
    TM1640_Writer_Dates(3, 0x6d);
    while(1)
    {
   i=100000;
   while(i--);
   NUM = (NUM+1)%0xff;
  TM1640_Writer_Dates(0, NUM);
    
    }
}

void Init_System(void)
{
    Init_LED();
    Init_Key();
    Init_TM1640();
}
