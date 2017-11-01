/* 
 * File:   TM1640.h
 * Author: SuiFeng
 *
 * Created on 2015年12月3日, 下午3:22
 */

#ifndef TM1640_H
#define	TM1640_H

#define TM1640_DIN_1 RD5 = 1
#define TM1640_DIN_0 RD5 = 0
#define TM1640_CLK_1 RD6 = 1
#define TM1640_CLK_0 RD6 = 0
    
#define TM1640DIN_TRIS TRISD5
#define TM1640CLK_TRIS TRISD6
    
#define DELAY_TIME 1
    
void TM1640_Start(void);
void TM1640_Stop(void);
void TM1640_Show_Numbers(int Number);
void TM1640_Writer_Dates(unsigned char Addr, unsigned char Date);
void TM1640_Writer_Byte(unsigned char Date);
void Open_Display(void);
void Disable_Display(void);
void TM1640_Delay(unsigned char Time);
void Init_TM1640(void);
void TM1640_Show_integer(  unsigned int Numbers);
void TM1640_Show_integer(  unsigned int Numbers);

#endif	/* TM1640_H */

