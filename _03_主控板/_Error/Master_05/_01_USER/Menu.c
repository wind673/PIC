/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Menu.c
* @Description : None
* @Date         : 2015/12/24
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : 工程的主要运行源文件
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/                  
#include <pic18f67k22.h>                //PIC官方函数库
#include "My_Types.h"                   //自定义的习惯写法定义
#include "Menu.h"                       //菜单
#include "TM1640.h"
#include "Key.h"
#include "Run.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/

/* 私有（静态）函数声明 --------------------------------------------------------*/
                                                                                                                                                                                                                                                                                 
/* 全局变量定义 ---------------------------------------------------------------*/
Menu_Def gs_Menu = {0}; //目录菜单

/* 全局函数编写 ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : Menu_Init()     
* @Description   : 菜单初始化
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/24
* @Explain       : None
------------------------------------------------------------------------------*/
void Menu_Init(void)
{
                                           
}


void MenuLock(void)
{
   if ( gs_Local_Key_User.key_group == KEY_4_5 && gs_Local_Key_User.key_group_state ==  KEY_short ) 
    {
        if( gs_Menu.Lock ==1)  gs_Switch.Magnet = 1;  //（已锁）菜单下才能充磁        
        Key_ResetFSM();  //读完组合按键，则其他按键皆无效              
    }
   
}

void MenuUnlock(void)
{
    TM1640_Show_integer(6666);
}

void Mune1(void)
{
    TM1640_Show_integer(1111);
}

void Mune2(void)
{
    TM1640_Show_integer(2222);
}

void Mune3(void)
{
    TM1640_Show_integer(3333);
}

void Mune4(void)
{
    TM1640_Show_integer(4444);
}




/**----------------------------------------------------------------------------
* @Function_Name : Menu_Run()     
* @Description   : 菜单运行
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/24
* @Explain       : None
------------------------------------------------------------------------------*/
void Menu_Run(void)
{
    Key_ReadFSM();
    if(gs_Menu.Lock) MenuLock();
    else  
    {
        if(gs_Menu.Level == 0) MenuUnlock();   
        else if(gs_Menu.Level == 1) Mune1();    
        else if(gs_Menu.Level == 2) Mune2();    
        else if(gs_Menu.Level == 3) Mune3();    
        else if(gs_Menu.Level == 4) Mune4();    
    }
    Key_ResetFSM();  
}  


/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

