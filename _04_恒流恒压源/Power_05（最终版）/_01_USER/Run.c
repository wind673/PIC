/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

/**============================================================================
* @File_Name   : Run.c
* @Description : None
* @Date         : 2015/12/9
* @By           : WindRises（谢玉伸）
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include "Run.h"
#include <pic18f67k22.h>                //PIC官方函数库
#include "Config_18F167K22.h"           //配置PIC芯片   
#include "My_Delay.h"                   //延时 
#include "My_Types.h"                   //自定义的习惯写法定义
#include "Key.h"                        //简写定义
#include "Nixie.h"                     //LED显示
#include "My_Timer.h"                   //定时器
#include "IR2184.h"   
#include "EEPROM.h"

/* 私有宏定义 -----------------------------------------------------------------*/

/* 私有变量定义 ---------------------------------------------------------------*/  

/* 私有（静态）函数声明 --------------------------------------------------------*/

/* 全局变量定义 ---------------------------------------------------------------*/ 
unsigned int IR2184_Timer = 0;

/* 全局变量声明 ---------------------------------------------------------------*/ 
extern unsigned char IR2184_Num;
extern unsigned char Nix_Flash;

/* 全局函数编写 ---------------------------------------------------------------*/


/**----------------------------------------------------------------------------
* @Function_Name : Manage_Message()     
* @Description   : 处理函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Manage_Message(void)
{
    unsigned char _databuff[1] = {0};
    
    Key_FSM_Read();
    /* 组合按键1,2 ------------------------*/  
    if ( Local_Key_User.key_group == KEY_1_2 && Local_Key_User.key_group_state ==  KEY_short )  
    {   
        _databuff[0] = IR2184_Num ;
        EEPROM_Writers(0x10,_databuff,1); //存储新数据
        Nix_Flash = 130;  //闪烁时间 130*10ms =1.3s
    }                   
    
    /* 按键1 -----------------------------*/  
    if (Local_Key_User.key_state[1-1] == KEY_short)  IR2184_Num -- ; //判断按键1是否短按
    if (Local_Key_User.key_state[1-1] == KEY_hold)   IR2184_Num -- ; //判断按键1是否长按
    
    /* 按键2 -----------------------------*/  
    if (Local_Key_User.key_state[2-1] == KEY_short)  IR2184_Num ++ ; //判断按键2是否短按
    if (Local_Key_User.key_state[2-1] == KEY_hold)   IR2184_Num ++ ; //判断按键2是否长按
   
    if(IR2184_Num > 99 && IR2184_Num <200 ) IR2184_Num = 0;
    if(IR2184_Num > 200 ) IR2184_Num = 99;
    
    Key_FSM_Reset();
}


/**----------------------------------------------------------------------------
* @Function_Name : Run()     
* @Description   : 运行函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Run(void)
{
    if( IR2184_INPUT_1 == 0 ) 
    {
        delay_ms(20);  //20ms防抖，去干扰
        if( IR2184_INPUT_1 == 0 ) 
        {
            IR2184_Timer = 0;         
            IR2184_ON_1();      
            while( IR2184_Timer < IR2184_Num ); 
            IR2184_OFF_1(); 
        }
         
    }
    
    if( IR2184_INPUT_2 == 0 ) 
    {
        delay_ms(20);  //20ms防抖，去干扰
        if( IR2184_INPUT_2 == 0 )
        {
            IR2184_Timer = 0;
            IR2184_ON_2(); 
            while( IR2184_Timer < IR2184_Num );
            IR2184_OFF_2(); 
        }
        
    }
     
}


/**----------------------------------------------------------------------------
* @Function_Name : Show_Result()     
* @Description   : 显示函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/9
* @Explain       : None
------------------------------------------------------------------------------*/
void Show_Result(void)
{ 
    Nixie_ShowNum(IR2184_Num);  //显示两位
}

/**----------------------------------------------------------------------------
* @Function_Name : Sys_Init()     
* @Description   : 系统初始化函数
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2016/2/21
* @Explain       : None
------------------------------------------------------------------------------*/
void Sys_Init(void)
{
    /* 变量定义 --------------------------------*/
    unsigned char _databuff[1] = {0};
    
    /* 初始化 --------------------------------*/
    WDTCON = 1;    //开启看门狗
    CLRWDT();
    Key_Init();       //按键     
    Timer0_Init();    //定时器   
    Nixie_Init();     //数码管
    IR2184_Init();    //高速半桥激励器
    Key_Init();        //按键初始化
    
    EEPROM_Reads(0x10,_databuff,1); //读取存储的数据
    IR2184_Num = _databuff[0];
    

}

/*******************************(C) COPYRIGHT 2015 WindRises（谢玉伸）*********************************/

