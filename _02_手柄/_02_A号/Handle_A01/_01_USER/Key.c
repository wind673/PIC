/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Key.c
* @Description : None
* @Date         : 2015/10/29
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "Key.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/
static void Key_Scan(void);//按键扫描函数的私定义

/* 全局变量定义 ---------------------------------------------------------------*/
__Def_Key_FSM Local_Key_FSM ={KEY_default,{0,0,0,0},KEY_default,{0,0,0,0}};//定义一个状态机结构体

/* 全局函数编写 ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : Key_Init()     
* @Description   : 按键的初始化函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/11/1
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_Init(void)
{
    TRISE |= 0x1e; //将E 2,3,4配置成输入(写入1用 | )
    TRISD |= 0xc0; //将D 6,7, 配置成输入(写入1用 | )
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_Scan()     
* @Description   : 按键的扫描函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
static void Key_Scan(void)
{
    Local_Key_FSM.key_state = 0x00;//初始化按键状态
    //检测各按键现状
    if( KEY_1 == 0 )  Local_Key_FSM.key_state |= (0x01 << 0)  ; 
    if( KEY_2 == 0 )  Local_Key_FSM.key_state |= (0x01 << 1)  ; 
    if( KEY_3 == 0 )  Local_Key_FSM.key_state |= (0x01 << 2)  ; 
    if( KEY_4 == 0 )  Local_Key_FSM.key_state |= (0x01 << 3)  ; 
    if( KEY_5 == 0 )  Local_Key_FSM.key_state |= (0x01 << 4)  ; 
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_FSM_Scan()     
* @Description   : 按键状态机的扫描函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/11/17
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_FSM_Scan(void)
{
    Key_Scan();//扫描当前按键状态
    if( Local_Key_FSM.key_state & 0x01 ) Local_Key_FSM.key[0]++;//判断按键0的状态
    if( Local_Key_FSM.key_state & 0x02 ) Local_Key_FSM.key[1]++;//判断按键1的状态
    if( Local_Key_FSM.key_state & 0x04 ) Local_Key_FSM.key[2]++;//判断按键2的状态
    if( Local_Key_FSM.key_state & 0x08 ) Local_Key_FSM.key[3]++;//判断按键3的状态
    if( Local_Key_FSM.key_state & 0x10 ) Local_Key_FSM.key[4]++;//判断按键4的状态
    
    if(  Local_Key_FSM.key_state == 0x00 )     //单独按键复位
    {
        Local_Key_FSM.key[0] = 0;
        Local_Key_FSM.key[1] = 0;
        Local_Key_FSM.key[2] = 0;
        Local_Key_FSM.key[3] = 0;
        Local_Key_FSM.key[4] = 0;
    }
    else
    {
        /*---------------- 判断单个按键 ----------------*/
        if( Local_Key_FSM.key[0] < KEY_short_Time )  Local_Key_FSM.key_FSM[0] = KEY_default;//无效状态
        else if( Local_Key_FSM.key[0] < KEY_hold_Time )  Local_Key_FSM.key_FSM[0] = KEY_short; //判断按键的状态机短按
        else  Local_Key_FSM.key_FSM[0] = KEY_hold; //判断按键的状态机长按   

        if( Local_Key_FSM.key[1] < KEY_short_Time )  Local_Key_FSM.key_FSM[1] = KEY_default;//无效状态
        else if( Local_Key_FSM.key[1] < KEY_hold_Time )  Local_Key_FSM.key_FSM[1] = KEY_short; //判断按键的状态机短按
        else  Local_Key_FSM.key_FSM[1] = KEY_hold; //判断按键的状态机长按   

        if( Local_Key_FSM.key[2] < KEY_short_Time )  Local_Key_FSM.key_FSM[2] = KEY_default;//无效状态
        else if( Local_Key_FSM.key[2] < KEY_hold_Time )  Local_Key_FSM.key_FSM[2] = KEY_short; //判断按键的状态机短按
        else  Local_Key_FSM.key_FSM[2] = KEY_hold; //判断按键的状态机长按   

        if( Local_Key_FSM.key[3] < KEY_short_Time )  Local_Key_FSM.key_FSM[3] = KEY_default;//无效状态
        else if( Local_Key_FSM.key[3] < KEY_hold_Time )  Local_Key_FSM.key_FSM[3] = KEY_short; //判断按键的状态机短按
        else  Local_Key_FSM.key_FSM[3] = KEY_hold; //判断按键的状态机长按   

        if( Local_Key_FSM.key[4] < KEY_short_Time )  Local_Key_FSM.key_FSM[4] = KEY_default;//无效状态
        else if( Local_Key_FSM.key[4] < KEY_hold_Time )  Local_Key_FSM.key_FSM[4] = KEY_short; //判断按键的状态机短按
        else  Local_Key_FSM.key_FSM[4] = KEY_hold; //判断按键的状态机长按   

       /*---------------- 判断组合按键 ----------------*/
        Local_Key_FSM.key_group = KEY_default;//初始化按键组合状态
        if( Local_Key_FSM.key_FSM[0] != KEY_default ) Local_Key_FSM.key_group |=  0x01<<0;
        if( Local_Key_FSM.key_FSM[1] != KEY_default ) Local_Key_FSM.key_group |=  0x01<<1;
        if( Local_Key_FSM.key_FSM[2] != KEY_default ) Local_Key_FSM.key_group |=  0x01<<2;
        if( Local_Key_FSM.key_FSM[3] != KEY_default ) Local_Key_FSM.key_group |=  0x01<<3;
        if( Local_Key_FSM.key_FSM[4] != KEY_default ) Local_Key_FSM.key_group |=  0x01<<4;
    }                                                                                                   
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_FSM_Reset()     
* @Description   : 按键状态机复位函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/11/21
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_FSM_Reset(void)
{
    /*---------------- 状态机复位 ----------------*/ 
    Local_Key_FSM.key_FSM[0] = KEY_default;
    Local_Key_FSM.key_FSM[1] = KEY_default;
    Local_Key_FSM.key_FSM[2] = KEY_default;
    Local_Key_FSM.key_FSM[3] = KEY_default;
    Local_Key_FSM.key_FSM[4] = KEY_default;
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_FSM_Read()     
* @Description   : 按键状态机读取函数
* @Parameter     :  key_num 按键序号 /组合（KEY_group）
* @Return        :  状态值
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/11/21
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned char Key_FSM_Read( unsigned char key_num)
{
    unsigned char temp;
    if( key_num != KEY_group ) //单独按键数据
    {
        if( Local_Key_FSM.key_state == 0x00 )  //按键空闲状态 
        {
            temp = Local_Key_FSM.key_FSM[key_num-1];
            Local_Key_FSM.key_FSM[key_num-1] = KEY_default; //若是短按，则重置该按键的状态机,为下次做准备
            return temp;
        }
        //按键繁忙状态下返回忙碌状态(被按下)  
        else return KEY_busy;
    }
    
    if ( key_num == KEY_group ) //组合按键数据
    {
        if( Local_Key_FSM.key_state == 0x00 )  //按键空闲状态下
        {
        temp = Local_Key_FSM.key_group; 
        Local_Key_FSM.key_group = KEY_default; //重置该按键的状态机
        return temp;
        }
        //按键繁忙状态下返回忙碌状态(被按下) 
        else return KEY_busy;
    }
}

/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/
