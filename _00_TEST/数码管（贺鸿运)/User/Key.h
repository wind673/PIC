/* 
 * File:   Key.h
 * Author: SuiFeng
 *
 * Created on 2015年12月2日, 下午1:28
 */

#ifndef KEY_H
#define	KEY_H

#ifdef	__cplusplus
extern "C" {
#endif

#define KEY_1 (unsigned char)0x01
#define KEY_2 (unsigned char)0x02
#define KEY_3 (unsigned char)0x04
#define KEY_4 (unsigned char)0x08
#define KEY_5 (unsigned char)0x10
    
#define KEY_1_IO RE3
#define KEY_2_IO RE2
#define KEY_3_IO RD6
#define KEY_4_IO RE4
#define KEY_5_IO RD7

#define ENABLE 1
#define DISABLE 0
    
void Init_Key(void);
unsigned char Scanf_Key(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* KEY_H */

