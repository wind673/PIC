/* 
 * File:   EEPROM.h
 * Author: SuiFeng
 *
 * Created on 2015年12月12日, 上午11:25
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#define EEPROM_BYTE_VALUE 1024
    
unsigned char EEPROM_Reads(unsigned int Addr, unsigned char *DateBuff, unsigned int length);
unsigned char EEPROM_Writers(unsigned int Addr, unsigned char *DateBuff, unsigned int length);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

