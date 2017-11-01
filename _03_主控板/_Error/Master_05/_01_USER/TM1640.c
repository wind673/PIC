/*
 * File:   TM1640.c
 * Author: SuiFeng
 * brief: 面板LED数码管的初始化与值写入
 * Created on 2015年12月3日, 下午3:22
 */


#include <xc.h>
#include "TM1640.h"
#include "Menu.h"                       //菜单

//共阴级数码管段码
const unsigned char LED_Number[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};       
const unsigned char LED_UI[UI_E+1] = {0};

/******************************************************************************
*     Function Name:    TM1640_Stop                                           *
*     Return Value:     void                                                  *
*     Parameters:       void                                                  *
*     Description:      初始化TM1640                                          *
*******************************************************************************/
void Init_TM1640(void)
{
    /* 配置TM1640引脚为输出模式 */
    TM1640DIN_TRIS = 0;
    TM1640CLK_TRIS = 0;
    
    TM1640_Stop();
    
    TM1640_Start();
    TM1640_Writer_Byte(0x44);
    TM1640_Stop();
    
    TM1640_Start();
    TM1640_Writer_Byte(0x8F);
    TM1640_Stop();
}

/******************************************************************************
*     Function Name:    TM1640_Stop                                           *
*     Return Value:     void                                                  *
*     Parameters:       void                                                  *
*     Description:      TM1640起始信号                                         *
*******************************************************************************/
void TM1640_Start(void)
{
    TM1640_CLK_0;
    TM1640_Delay(DELAY_TIME);
    TM1640_DIN_1;
    TM1640_Delay(DELAY_TIME);
    TM1640_CLK_1;
    TM1640_Delay(DELAY_TIME);
    TM1640_DIN_0;
    TM1640_Delay(DELAY_TIME);
    TM1640_CLK_0;
}

/******************************************************************************
*     Function Name:    TM1640_Stop                                           *
*     Return Value:     void                                                  *
*     Parameters:       void                                                  *
*     Description:      TM1640停止信号                                        *
*******************************************************************************/
void TM1640_Stop(void)
{
    TM1640_CLK_0;
    TM1640_Delay(DELAY_TIME);
    TM1640_DIN_0;
    TM1640_Delay(DELAY_TIME);
    TM1640_CLK_1;
    TM1640_Delay(DELAY_TIME);
    TM1640_DIN_1;
    TM1640_Delay(DELAY_TIME);
    TM1640_CLK_0;
}

/******************************************************************************
*     Function Name:    TM1640_Show_Numbers                                   *
*     Return Value:     void                                                  *
*     Parameters:       Number:要写入的整型数值                                *
*     Description:      在四个LED上写入相应的整型数值                           *
*******************************************************************************/
void TM1640_Show_Numbers(int Number)
{
    if((Number < 10000) && (Number >= 0))
    {
        TM1640_Writer_Dates(3, LED_Number[Number / 1 % 10]);
        TM1640_Writer_Dates(2, LED_Number[Number / 10 % 10]);
        TM1640_Writer_Dates(1, LED_Number[Number / 100 % 10]);
        TM1640_Writer_Dates(0, LED_Number[Number / 1000 % 10]);
    }
}

/******************************************************************************
*     Function Name:    TM1640_Writer_Dates                                   *
*     Return Value:     void                                                  *
*     Parameters:       Addr:要写入的地址  Date:要写入的数据                    *
*     Description:      在相应的地址下写入相应的数据                            *
*******************************************************************************/
void TM1640_Writer_Dates(unsigned char Addr, unsigned char Date)
{
    if((Addr >= 0) && (Addr <= 15))
    {
        TM1640_Start();
        TM1640_Writer_Byte(0xC0 + Addr);
        TM1640_Writer_Byte(Date);
        TM1640_Stop();
    }
}

/******************************************************************************
*     Function Name:    TM1640_Writer_Byte                                    *
*     Return Value:     void                                                  *
*     Parameters:       Date:要写入的数据                                      *
*     Description:      写入数据                                               *
*******************************************************************************/
void TM1640_Writer_Byte(unsigned char Date)
{
    unsigned char mask;
    
    for(mask=0x01; mask; mask<<=1)
    {
        TM1640_CLK_0;
        TM1640_Delay(DELAY_TIME);
        if(mask & Date)
            TM1640_DIN_1;
        else
            TM1640_DIN_0;
        TM1640_Delay(DELAY_TIME);
        TM1640_CLK_1;
        TM1640_Delay(DELAY_TIME);
    }
}

/******************************************************************************
*     Function Name:    Open_Display                                          *
*     Return Value:     void                                                  *
*     Parameters:       void                                                  *
*     Description:      开启LED显示                                           *
*******************************************************************************/
void Open_Display(void)
{
    TM1640_Start();
    TM1640_Writer_Byte(0x8F);
    TM1640_Stop();
}

/******************************************************************************
*     Function Name:    Disable_Display                                          *
*     Return Value:     void                                                  *
*     Parameters:       void                                                  *
*     Description:      关闭LED显示                                           *
*******************************************************************************/
void Disable_Display(void)
{
    TM1640_Start();
    TM1640_Writer_Byte(0x80);
    TM1640_Stop();
}

/******************************************************************************
*     Function Name:    TM1640_Delay                                          *
*     Return Value:     void                                                  *
*     Parameters:       Time:所要延时的时间(us)                                *
*     Description:      延时函数                                              *
*******************************************************************************/
void TM1640_Delay(unsigned char Time)
{
    unsigned char i;
    
    do
    {
        for(i=0; i<10; ++i);
    }while(--Time);
}


/**----------------------------------------------------------------------------
* @Function_Name : TM1640_Show_Decimal()      
* @Description   : 显示实数（保留2位）
* @Parameter     : Decimal:需要显示的实数
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/17
* @Explain       : None
------------------------------------------------------------------------------*/
void TM1640_Show_Decimal( float Decimal)
{
    Decimal *= 100; //左移两位 
    //数码管位数（数码管排列从左往右 依次 0 ~ 3）
    TM1640_Writer_Dates(3,LED_Number[(int)Decimal%10]); Decimal/=10;         //数码管0
    TM1640_Writer_Dates(2,LED_Number[(int)Decimal%10]); Decimal/=10;         //数码管1 
    TM1640_Writer_Dates(1,LED_Number[(int)Decimal%10]|0x80); Decimal/=10;    //数码管2 显示点
    TM1640_Writer_Dates(0,LED_Number[(int)Decimal%10]);                      //数码管3
}


/**----------------------------------------------------------------------------
* @Function_Name : TM1640_Show_integer()      
* @Description   : 显示整数（保留2位）
* @Parameter     : Numbers： 需要显示的整数
* @Return        : void
* @Programer     : WindRises（谢玉伸）
* @Data          : 2015/12/17
* @Explain       : None
------------------------------------------------------------------------------*/
void TM1640_Show_integer(  unsigned int Numbers)
{
  //数码管位数（数码管排列从左往右 依次 0 ~ 3）
    TM1640_Writer_Dates(3,LED_Number[Numbers%10]); Numbers/=10;               //数码管0
    TM1640_Writer_Dates(2,LED_Number[Numbers%10]); Numbers/=10;               //数码管1 
    TM1640_Writer_Dates(1,LED_Number[Numbers%10]); Numbers/=10;               //数码管2
    TM1640_Writer_Dates(0,LED_Number[Numbers%10]);                            //数码管3
}




