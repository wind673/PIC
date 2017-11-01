/*
 * File:   TM1640.c
 * Author: SuiFeng
 *
 * Created on 2015年12月3日, 下午3:22
 */


#include <xc.h>
#include "TM1640.h"

#define cha 0x3F

//共阴级数码管段码
unsigned char LED_Number[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

void TM1640_Start(void)
{
    TM1640_CLK_0;
    TM1640_Delay(DELAY_TIME);
    TM1640_DIN_1;
    TM1640_Delay(DELAY_TIME);
    TM1640_CLK_1;
    TM1640_Delay(DELAY_TIME);
    TM1640_DIN_0;
    TM1640_Delay(DELAY_TIME);
    TM1640_CLK_0;
}

void TM1640_Stop(void)
{
    TM1640_CLK_0;
    TM1640_Delay(DELAY_TIME);
    TM1640_DIN_0;
    TM1640_Delay(DELAY_TIME);
    TM1640_CLK_1;
    TM1640_Delay(DELAY_TIME);
    TM1640_DIN_1;
    TM1640_Delay(DELAY_TIME);
    TM1640_CLK_0;
}

void TM1640_Show_Numbers(int Numbers)
{
    unsigned char Num = 0;
    
    while(Num < 4)
    {
        switch(Num)
        {
            case 0: switch(Numbers % 10)
            {
                case 0: TM1640_Writer_Dates(3, 0x3f); break;
                case 1: TM1640_Writer_Dates(3, 0x06); break;
                case 2: TM1640_Writer_Dates(3, 0x5b); break;
                case 3: TM1640_Writer_Dates(3, 0x4f); break;
                case 4: TM1640_Writer_Dates(3, 0x66); break;
                case 5: TM1640_Writer_Dates(3, 0x6d); break;
                case 6: TM1640_Writer_Dates(3, 0x7d); break;
                case 7: TM1640_Writer_Dates(3, 0x07); break;
                case 8: TM1640_Writer_Dates(3, 0x7f); break;
                case 9: TM1640_Writer_Dates(3, 0x6f); break;
            }   break;
            case 1: switch(Numbers % 10)
            {
                case 0: TM1640_Writer_Dates(2, 0x3f); break;
                case 1: TM1640_Writer_Dates(2, 0x06); break;
                case 2: TM1640_Writer_Dates(2, 0x5b); break;
                case 3: TM1640_Writer_Dates(2, 0x4f); break;
                case 4: TM1640_Writer_Dates(2, 0x66); break;
                case 5: TM1640_Writer_Dates(2, 0x6d); break;
                case 6: TM1640_Writer_Dates(2, 0x7d); break;
                case 7: TM1640_Writer_Dates(2, 0x07); break;
                case 8: TM1640_Writer_Dates(2, 0x7f); break;
                case 9: TM1640_Writer_Dates(2, 0x6f); break;
            }   break;
            case 2: switch(Numbers % 10)
            {
                case 0: TM1640_Writer_Dates(1, 0x3f); break;
                case 1: TM1640_Writer_Dates(1, 0x06); break;
                case 2: TM1640_Writer_Dates(1, 0x5b); break;
                case 3: TM1640_Writer_Dates(1, 0x4f); break;
                case 4: TM1640_Writer_Dates(1, 0x66); break;
                case 5: TM1640_Writer_Dates(1, 0x6d); break;
                case 6: TM1640_Writer_Dates(1, 0x7d); break;
                case 7: TM1640_Writer_Dates(1, 0x07); break;
                case 8: TM1640_Writer_Dates(1, 0x7f); break;
                case 9: TM1640_Writer_Dates(1, 0x6f); break;
            }   break;
            case 3: switch(Numbers % 10)
            {
                case 0: TM1640_Writer_Dates(0, 0x3f); break;
                case 1: TM1640_Writer_Dates(0, 0x06); break;
                case 2: TM1640_Writer_Dates(0, 0x5b); break;
                case 3: TM1640_Writer_Dates(0, 0x4f); break;
                case 4: TM1640_Writer_Dates(0, 0x66); break;
                case 5: TM1640_Writer_Dates(0, 0x6d); break;
                case 6: TM1640_Writer_Dates(0, 0x7d); break;
                case 7: TM1640_Writer_Dates(0, 0x07); break;
                case 8: TM1640_Writer_Dates(0, 0x7f); break;
                case 9: TM1640_Writer_Dates(0, 0x6f); break;
            }   break;
        }
        ++Num;
        Numbers /= 10;
    }
}

void TM1640_Writer_Dates(unsigned char Addr, unsigned char Date)
{
    if((Addr >= 0) && (Addr <= 3))
    {
        TM1640_Start();
        TM1640_Writer_Byte(0xC0 + Addr);
        TM1640_Writer_Byte(Date);
        TM1640_Stop();
    }
}

void TM1640_Writer_Byte(const unsigned char Date)
{
    unsigned char mask;
    
    for(mask=0x01; mask; mask<<=1)
    {
        TM1640_CLK_0;
        TM1640_Delay(DELAY_TIME);
        if(mask & Date)
            TM1640_DIN_1;
        else
            TM1640_DIN_0;
        TM1640_Delay(DELAY_TIME);
        TM1640_CLK_1;
        TM1640_Delay(DELAY_TIME);
    }
}

void Open_Display(void)
{
    TM1640_Start();
    TM1640_Writer_Byte(0x8F);
    TM1640_Stop();
}

void Disable_Display(void)
{
    TM1640_Start();
    TM1640_Writer_Byte(0x80);
    TM1640_Stop();
}

void TM1640_Delay(unsigned char Time)
{
    unsigned char i;
    
    do
    {
        for(i=0; i<10; ++i);
    }while(--Time);
}

void Init_TM1640(void)
{
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 0;
    TM1640_Stop();
    
    TM1640_Start();
    TM1640_Writer_Byte(0x44);
    TM1640_Stop();
    
    TM1640_Start();
    TM1640_Writer_Byte(0x8F);
    TM1640_Stop();
}
