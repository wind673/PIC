/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : SCR.c
* @Description : �ɿع���������Դ�ļ�
* @Date         : 2015/12/19
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/                  
#include <pic18f67k22.h>                //PIC�ٷ�������          
#include "My_Types.h"                   //�Զ����ϰ��д������     
#include "SCR.h"                        //�̵���            
#include "Run.h"                        //��Ҫ���к���
#include "Relay.h"                      //�̵���
#include "My_Delay.h"                   //��ʱ����

/* ˽�к궨�� -----------------------------------------------------------------*/
#define PULSE_CNT 8  //����1Khz����ĸ��� 

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/
void Delay_1Khz(void);   //��� -1us

/* ȫ�ֱ������� ---------------------------------------------------------------*/
  
/* ȫ�ֺ�����д ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : SCR_Magnet()     
* @Description   : ��ź���
* @Parameter     : _ch:���ͨ��
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/19
* @Explain       : None
------------------------------------------------------------------------------*/
void SCR_Magnet(unsigned char _ch)
{
//    ��ʱ��ģ����
    Relay_Control(_ch,1);                   
    delay_ms(100);
    Relay_Control(_ch,0);     
    gs_Switch.a_Magnet[_ch] = 0;
}

/**----------------------------------------------------------------------------
* @Function_Name : SCR_Demagnet()     
* @Description   : �˴ź���
* @Parameter     : _ch:�˴�ͨ��
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/19
* @Explain       : None
------------------------------------------------------------------------------*/
void SCR_Demagnet(unsigned char _ch)
{
    //��ʱ��ģ���˴�
    Relay_Control(_ch,1);                   
    delay_ms(100);
    Relay_Control(_ch,0);
    gs_Switch.a_Demagnet[_ch] = 0;
}

/**----------------------------------------------------------------------------
* @Function_Name : SCR_Init()     
* @Description   : �̵�����ʼ��
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/12/19
* @Explain       : None
------------------------------------------------------------------------------*/
void SCR_Init(void)
{
     /*��ʼ���ɿع��IO�� ----------------------*/
    RB1 = 0;       
    RB0 = 0;
    
    /*���ÿɿع��IO�� -----------------------*/
    TRISB1 = 0;  //QD1 :�ɿع�ķ���ͨ
    TRISB0 = 0;  //QD2 :�ɿع������ͨ
    
    /*���ù�����IO�� -----------------------*/
    TRISB2 = 1;  //������IO�ڣ�����ģʽ
}


/**----------------------------------------------------------------------------
* @Function_Name : Delay_3Khz()	       
* @Description   : ��ʱ��׼1.5ms
* @Parameter     : coid
* @Return         : void
* @Programer     : WindRises��л���죩
* @Data           : 2015/12/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Delay_3Khz(void)   //��� -1us
{
    unsigned char a,b,c;
    for(c=3;c>0;c--)
        for(b=32;b>0;b--)
            for(a=2;a>0;a--);
}

/**----------------------------------------------------------------------------
* @Function_Name : Pulse_1Khz()       
* @Description   : ����1Khz����
* @Parameter     : _QD�����͵�IO��
* @Return         : void
* @Programer     : WindRises��л���죩
* @Data           : 2015/12/15
* @Explain       : None
------------------------------------------------------------------------------*/
void Pulse_3Khz(unsigned char _QD)
{
    unsigned char _pulse = PULSE_CNT;  //PULSE_Number ������
    static unsigned char _overturn_3Khz = 0;
    
    /* ��QD1�˿ڷ���3Khz���� -----------------------*/
    if(_QD == 1)
    while( _pulse-- ) 
    {
        _overturn_3Khz =~ _overturn_3Khz;
        if(_overturn_3Khz) _3Khz_Out1_ON(); 
        else _3Khz_Out1_OFF();
        Delay_3Khz();
    } 
    
    /* ��QD2�˿ڷ���3Khz���� -----------------------*/
    if(_QD == 2)
    while( _pulse-- ) 
    {
        _overturn_3Khz =~ _overturn_3Khz;
        if(_overturn_3Khz) _3Khz_Out2_ON(); 
        else _3Khz_Out2_OFF();
        Delay_3Khz();
    
    }
    
}




/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

