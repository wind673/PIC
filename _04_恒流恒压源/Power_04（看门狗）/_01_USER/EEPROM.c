/* * File:   EEPROM.c
 * Author: SuiFeng
 * brief: 芯片内部EEPROM的读取与写入
 * Created on 2015年12月12日, 上午10:48
 */


#include <xc.h>
#include <EEP.h>
#include "EEPROM.h"

/******************************************************************************
*     Function Name:    EEPROM_Reads                                          *
*     Return Value:     0:successful;   1:error;                              *
*     Parameters:       Addr:读取地址  DateBuff:读取的数据  length:读取的长度   *
*     Description:      读取EERPOM数据                                         *
*******************************************************************************/
unsigned char EEPROM_Reads(unsigned int Addr, unsigned char *DateBuff, unsigned int length)
{
    unsigned char i;
    
    if(Addr + length <= EEPROM_BYTE_VALUE)
    {
        for(i=0; i<length; ++i)
            DateBuff[i] = Read_b_eep(Addr + i);
        return 0;   //读取成功
    }
    else
        return 1;   //读取失败
}

/******************************************************************************
*     Function Name:    EEPROM_Writers                                          *
*     Return Value:     0:successful;   1:error;                              *
*     Parameters:       Addr:写入地址  DateBuff:写入的数据  length:写入的长度   *
*     Description:      写入EERPOM数据                                         *
*******************************************************************************/
unsigned char EEPROM_Writers(unsigned int Addr, unsigned char *DateBuff, unsigned int length)
{
    unsigned char i;
    
    if(Addr + length <= EEPROM_BYTE_VALUE)
    {
        for(i=0; i<length; ++i)
            Write_b_eep(Addr + i, DateBuff[i]);
        return 0;   //写入成功
    }
    else
        return 1;   //写入失败
}


