/*
 * File:   TM1640.c
 * Author: SuiFeng
 * brief: ���LED����ܵĳ�ʼ����ֵд��
 * Created on 2015��12��3��, ����3:22
 */


#include <xc.h>
#include "TM1640.h"
#include "Menu.h"                       //�˵�

//����������ܶ���
const unsigned char LED_Number[16] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};       
const unsigned char LED_UI[UI_E+1] = {0};

/******************************************************************************
*     Function Name:    TM1640_Stop                                           *
*     Return Value:     void                                                  *
*     Parameters:       void                                                  *
*     Description:      ��ʼ��TM1640                                          *
*******************************************************************************/
void Init_TM1640(void)
{
    /* ����TM1640����Ϊ���ģʽ */
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
*     Description:      TM1640��ʼ�ź�                                         *
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
*     Description:      TM1640ֹͣ�ź�                                        *
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
*     Parameters:       Number:Ҫд���������ֵ                                *
*     Description:      ���ĸ�LED��д����Ӧ��������ֵ                           *
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
*     Parameters:       Addr:Ҫд��ĵ�ַ  Date:Ҫд�������                    *
*     Description:      ����Ӧ�ĵ�ַ��д����Ӧ������                            *
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
*     Parameters:       Date:Ҫд�������                                      *
*     Description:      д������                                               *
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
*     Description:      ����LED��ʾ                                           *
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
*     Description:      �ر�LED��ʾ                                           *
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
*     Parameters:       Time:��Ҫ��ʱ��ʱ��(us)                                *
*     Description:      ��ʱ����                                              *
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
* @Description   : ��ʾʵ��������2λ��
* @Parameter     : Decimal:��Ҫ��ʾ��ʵ��
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/17
* @Explain       : None
------------------------------------------------------------------------------*/
void TM1640_Show_Decimal( float Decimal)
{
    Decimal *= 100; //������λ 
    //�����λ������������д������� ���� 0 ~ 3��
    TM1640_Writer_Dates(3,LED_Number[(int)Decimal%10]); Decimal/=10;         //�����0
    TM1640_Writer_Dates(2,LED_Number[(int)Decimal%10]); Decimal/=10;         //�����1 
    TM1640_Writer_Dates(1,LED_Number[(int)Decimal%10]|0x80); Decimal/=10;    //�����2 ��ʾ��
    TM1640_Writer_Dates(0,LED_Number[(int)Decimal%10]);                      //�����3
}


/**----------------------------------------------------------------------------
* @Function_Name : TM1640_Show_integer()      
* @Description   : ��ʾ����������2λ��
* @Parameter     : Numbers�� ��Ҫ��ʾ������
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/17
* @Explain       : None
------------------------------------------------------------------------------*/
void TM1640_Show_integer(  unsigned int Numbers)
{
  //�����λ������������д������� ���� 0 ~ 3��
    TM1640_Writer_Dates(3,LED_Number[Numbers%10]); Numbers/=10;               //�����0
    TM1640_Writer_Dates(2,LED_Number[Numbers%10]); Numbers/=10;               //�����1 
    TM1640_Writer_Dates(1,LED_Number[Numbers%10]); Numbers/=10;               //�����2
    TM1640_Writer_Dates(0,LED_Number[Numbers%10]);                            //�����3
}




