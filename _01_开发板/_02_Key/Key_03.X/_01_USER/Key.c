/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : Key.c
* @Description : None
* @Date         : 2015/10/29
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include <pic18f67k22.h>
#include "Key.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/
static void Key_Scan(void);//����ɨ�躯����˽����

/* ȫ�ֱ������� ---------------------------------------------------------------*/
__Def_Key_FSM Local_Key_FSM ={KEY_default,{0,0,0,0},KEY_default,{0,0,0,0}};//����һ��״̬���ṹ��

/* ȫ�ֺ�����д ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : Key_Init()     
* @Description   : �����ĳ�ʼ������
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/11/1
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_Init(void)
{
   TRISC |= 0x3c;//��C2,3,4,5���ó����(д��1�� | )     
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_Scan()     
* @Description   : ������ɨ�躯��
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/10/29
* @Explain       : None
------------------------------------------------------------------------------*/
static void Key_Scan(void)
{
    Local_Key_FSM.key_state = 0x00;//��ʼ������״̬
    //����������״
    if( RC2 == 0 )  Local_Key_FSM.key_state |= 0x01 ; else  Local_Key_FSM.key_state &= 0xff-0x01;
    if( RC3 == 0 )  Local_Key_FSM.key_state |= 0x02 ; else  Local_Key_FSM.key_state &= 0xff-0x02; 
    if( RC4 == 0 )  Local_Key_FSM.key_state |= 0x04 ; else  Local_Key_FSM.key_state &= 0xff-0x04;
    if( RC5 == 0 )  Local_Key_FSM.key_state |= 0x08 ; else  Local_Key_FSM.key_state &= 0xff-0x08;
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_FSM_Scan()     
* @Description   : ����״̬����ɨ�躯��
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/11/17
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_FSM_Scan(void)
{
    Key_Scan();//ɨ�赱ǰ����״̬
    if( Local_Key_FSM.key_state & 0x01 ) Local_Key_FSM.key[0]++;//�жϰ���0��״̬
    if( Local_Key_FSM.key_state & 0x02 ) Local_Key_FSM.key[1]++;//�жϰ���1��״̬
    if( Local_Key_FSM.key_state & 0x04 ) Local_Key_FSM.key[2]++;//�жϰ���2��״̬
    if( Local_Key_FSM.key_state & 0x08 ) Local_Key_FSM.key[3]++;//�жϰ���3��״̬
    
    if(  Local_Key_FSM.key_state == 0x00 )     //����������λ
    {
        Local_Key_FSM.key[0] = 0;
        Local_Key_FSM.key[1] = 0;
        Local_Key_FSM.key[2] = 0;
        Local_Key_FSM.key[3] = 0;
    }
    else
    {
        /*---------------- �жϵ������� ----------------*/
        if( Local_Key_FSM.key[0] < KEY_short_Time )  Local_Key_FSM.key_FSM[0] = KEY_default;//��Ч״̬
        else if( Local_Key_FSM.key[0] < KEY_hold_Time )  Local_Key_FSM.key_FSM[0] = KEY_short; //�жϰ�����״̬���̰�
        else  Local_Key_FSM.key_FSM[0] = KEY_hold; //�жϰ�����״̬������   

        if( Local_Key_FSM.key[1] < KEY_short_Time )  Local_Key_FSM.key_FSM[1] = KEY_default;//��Ч״̬
        else if( Local_Key_FSM.key[1] < KEY_hold_Time )  Local_Key_FSM.key_FSM[1] = KEY_short; //�жϰ�����״̬���̰�
        else  Local_Key_FSM.key_FSM[1] = KEY_hold; //�жϰ�����״̬������   

        if( Local_Key_FSM.key[2] < KEY_short_Time )  Local_Key_FSM.key_FSM[2] = KEY_default;//��Ч״̬
        else if( Local_Key_FSM.key[2] < KEY_hold_Time )  Local_Key_FSM.key_FSM[2] = KEY_short; //�жϰ�����״̬���̰�
        else  Local_Key_FSM.key_FSM[2] = KEY_hold; //�жϰ�����״̬������   

        if( Local_Key_FSM.key[3] < KEY_short_Time )  Local_Key_FSM.key_FSM[3] = KEY_default;//��Ч״̬
        else if( Local_Key_FSM.key[3] < KEY_hold_Time )  Local_Key_FSM.key_FSM[3] = KEY_short; //�жϰ�����״̬���̰�
        else  Local_Key_FSM.key_FSM[3] = KEY_hold; //�жϰ�����״̬������   

       /*---------------- �ж���ϰ��� ----------------*/
        Local_Key_FSM.key_group = KEY_default;//��ʼ���������״̬
        if( Local_Key_FSM.key_FSM[0] != KEY_default ) Local_Key_FSM.key_group |=  0x01;
        if( Local_Key_FSM.key_FSM[1] != KEY_default ) Local_Key_FSM.key_group |=  0x02;
        if( Local_Key_FSM.key_FSM[2] != KEY_default ) Local_Key_FSM.key_group |=  0x04;
        if( Local_Key_FSM.key_FSM[3] != KEY_default ) Local_Key_FSM.key_group |=  0x08;
    }                                                                                                   
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_FSM_Reset()     
* @Description   : ����״̬����λ����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
* @Data          : 2015/11/21
* @Explain       : None
------------------------------------------------------------------------------*/
void Key_FSM_Reset(void)
{
    /*---------------- ״̬����λ ----------------*/ 
    Local_Key_FSM.key_FSM[0] = KEY_default;
    Local_Key_FSM.key_FSM[1] = KEY_default;
    Local_Key_FSM.key_FSM[2] = KEY_default;
    Local_Key_FSM.key_FSM[3] = KEY_default;
    
}


/**----------------------------------------------------------------------------
* @Function_Name : Key_FSM_Read()     
* @Description   : ����״̬����ȡ����
* @Parameter     : unsigned char
* @Return        : unsigned char
* @Programer     : WindRises��л���죩
* @Data          : 2015/11/21
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned char Key_FSM_Read( unsigned char key_num)
{
    unsigned char temp;
    if( key_num < 10 ) //������������
    {
        if( Local_Key_FSM.key_state == 0x00 )  //��������״̬��
        {
            temp = Local_Key_FSM.key_FSM[key_num];
            Local_Key_FSM.key_FSM[key_num] = KEY_default; //���øð�����״̬��
            return temp;
        }
        //������æ״̬�·���æµ״̬(������)
        else return KEY_busy;
    }
    else if ( key_num == KEY_group ) //��ϰ�������
    {
        if( Local_Key_FSM.key_state == 0x00 )  //��������״̬��
        {
        temp = Local_Key_FSM.key_group; 
        Local_Key_FSM.key_group = KEY_default; //���øð�����״̬��
         return temp;
        }
        //������æ״̬�·���æµ״̬(������) 
        else return KEY_busy;
    }
}

/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/
