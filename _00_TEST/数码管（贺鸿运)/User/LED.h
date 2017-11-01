/* 
 * File:   LED.h
 * Author: SuiFeng
 *
 * Created on 2015年12月2日, 下午1:29
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LED_1 (unsigned char)0x01
#define LED_2 (unsigned char)0x02
#define LED_3 (unsigned char)0x04
    
#define LED_1_IO RE7
#define LED_2_IO RE6
#define LED_3_IO RE5
    
#define ENABLE 1
#define DISABLE 0
    
#define LIGHT 0
#define QUENCH 1

void Init_LED(void);
void Lighten_LED(unsigned char LED_Num);
void Quench_LED(unsigned char LED_Num);

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

