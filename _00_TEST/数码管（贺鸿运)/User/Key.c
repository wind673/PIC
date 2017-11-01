/*
 * File:   Key.c
 * Author: SuiFeng
 *
 * Created on 2015年12月2日, 下午1:28
 */


#include <xc.h>
#include "Key.h"

void Init_Key(void)
{
    TRISE2 = 1;
    TRISE3 = 1;
    TRISE4 = 1;
    TRISD6 = 1;
    TRISD7 = 1;
}

unsigned char Scanf_Key(void)
{
    unsigned char Flag, Keys = 0x00;
    unsigned char i;
    
    if(KEY_1_IO != 1)
    {
        Flag = 0xFF;
        for(i=0; i<8; ++i)
        {
            Flag <<= 1;
            Flag |= KEY_1_IO;
        }
        if(Flag == 0x00)
            Keys |= KEY_1;
    }
    if(KEY_2_IO != 1)
    {
        Flag = 0xFF;
        for(i=0; i<8; ++i)
        {
            Flag <<= 1;
            Flag |= KEY_2_IO;
        }
        if(Flag == 0x00)
            Keys |= KEY_2;
    }
    if(KEY_3_IO != 1)
    {
        Flag = 0xFF;
        for(i=0; i<8; ++i)
        {
            Flag <<= 1;
            Flag |= KEY_3_IO;
        }
        if(Flag == 0x00)
            Keys |= KEY_3;
    }
    if(KEY_4_IO != 1)
    {
        Flag = 0xFF;
        for(i=0; i<8; ++i)
        {
            Flag <<= 1;
            Flag |= KEY_4_IO;
        }
        if(Flag == 0x00)
            Keys |= KEY_4;
    }
    if(KEY_5_IO != 1)
    {
        Flag = 0xFF;
        for(i=0; i<8; ++i)
        {
            Flag <<= 1;
            Flag |= KEY_5_IO;
        }
        if(Flag == 0x00)
            Keys |= KEY_5;
    }
    return Keys;
}
