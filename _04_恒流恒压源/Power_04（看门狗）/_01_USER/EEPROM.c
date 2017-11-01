/* * File:   EEPROM.c
 * Author: SuiFeng
 * brief: оƬ�ڲ�EEPROM�Ķ�ȡ��д��
 * Created on 2015��12��12��, ����10:48
 */


#include <xc.h>
#include <EEP.h>
#include "EEPROM.h"

/******************************************************************************
*     Function Name:    EEPROM_Reads                                          *
*     Return Value:     0:successful;   1:error;                              *
*     Parameters:       Addr:��ȡ��ַ  DateBuff:��ȡ������  length:��ȡ�ĳ���   *
*     Description:      ��ȡEERPOM����                                         *
*******************************************************************************/
unsigned char EEPROM_Reads(unsigned int Addr, unsigned char *DateBuff, unsigned int length)
{
    unsigned char i;
    
    if(Addr + length <= EEPROM_BYTE_VALUE)
    {
        for(i=0; i<length; ++i)
            DateBuff[i] = Read_b_eep(Addr + i);
        return 0;   //��ȡ�ɹ�
    }
    else
        return 1;   //��ȡʧ��
}

/******************************************************************************
*     Function Name:    EEPROM_Writers                                          *
*     Return Value:     0:successful;   1:error;                              *
*     Parameters:       Addr:д���ַ  DateBuff:д�������  length:д��ĳ���   *
*     Description:      д��EERPOM����                                         *
*******************************************************************************/
unsigned char EEPROM_Writers(unsigned int Addr, unsigned char *DateBuff, unsigned int length)
{
    unsigned char i;
    
    if(Addr + length <= EEPROM_BYTE_VALUE)
    {
        for(i=0; i<length; ++i)
            Write_b_eep(Addr + i, DateBuff[i]);
        return 0;   //д��ɹ�
    }
    else
        return 1;   //д��ʧ��
}


