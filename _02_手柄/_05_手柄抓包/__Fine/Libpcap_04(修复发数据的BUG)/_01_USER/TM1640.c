/*
 * File:   TM1640.c
 * Author: SuiFeng
 *
 * Created on 2015年12月3日, 下午3:22
 */


#include <xc.h>
#include "TM1640.h"
#define NIXIE_LENTH 4  //数码管位数长度

#define cha 0x3F

//共阴级数码管段码
const unsigned char LED_Number[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};


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

void TM1640_Show_Decimal( float Numbers)
{
    Numbers *= 100; //左移两位 
    //数码管位数（数码管排列从左往右 依次 0 ~ 3）
    TM1640_Writer_Dates(3,LED_Number[(int)Numbers%10]); Numbers/=10;         //数码管0
    TM1640_Writer_Dates(2,LED_Number[(int)Numbers%10]); Numbers/=10;         //数码管1 
    TM1640_Writer_Dates(1,LED_Number[(int)Numbers%10]|0x80); Numbers/=10;    //数码管2 显示点
    TM1640_Writer_Dates(0,LED_Number[(int)Numbers%10]);                      //数码管3
}

void TM1640_Show_integer(  unsigned int Numbers)
{
  //数码管位数（数码管排列从左往右 依次 0 ~ 3）
    TM1640_Writer_Dates(3,LED_Number[Numbers%10]); Numbers/=10;               //数码管0
    TM1640_Writer_Dates(2,LED_Number[Numbers%10]); Numbers/=10;               //数码管1 
    TM1640_Writer_Dates(1,LED_Number[Numbers%10]); Numbers/=10;               //数码管2
    TM1640_Writer_Dates(0,LED_Number[Numbers%10]);                            //数码管3
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
