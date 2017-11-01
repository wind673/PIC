/* 
 * File:   TM1640.h
 * Author: SuiFeng
 *
 * Created on 2015年12月3日, 下午3:22
 */

#ifndef TM1640_H
#define	TM1640_H

#ifdef	__cplusplus
extern "C" {
#endif

#define TM1640_DIN_1 RC4 = 1
#define TM1640_DIN_0 RC4 = 0
#define TM1640_CLK_1 RC3 = 1
#define TM1640_CLK_0 RC3 = 0
    
#define DELAY_TIME 1
    
void TM1640_Start(void);
void TM1640_Stop(void);
void TM1640_Show_Numbers(int Numbers);
void TM1640_Writer_Dates(unsigned char Addr, unsigned char Date);
void TM1640_Writer_Byte(const unsigned char Date);
void Open_Display(void);
void Disable_Display(void);
void TM1640_Delay(unsigned char Time);
void Init_TM1640(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* TM1640_H */

