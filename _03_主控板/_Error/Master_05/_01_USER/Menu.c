/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

/**============================================================================
* @File_Name   : Menu.c
* @Description : None
* @Date         : 2015/12/24
* @By           : WindRises��л���죩
* @E_mail      : 1659567673@ qq.com
* @Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* @Explain     : ���̵���Ҫ����Դ�ļ�
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/                  
#include <pic18f67k22.h>                //PIC�ٷ�������
#include "My_Types.h"                   //�Զ����ϰ��д������
#include "Menu.h"                       //�˵�
#include "TM1640.h"
#include "Key.h"
#include "Run.h"

/* ˽�к궨�� -----------------------------------------------------------------*/

/* ˽�б������� ---------------------------------------------------------------*/

/* ˽�У���̬���������� --------------------------------------------------------*/
                                                                                                                                                                                                                                                                                 
/* ȫ�ֱ������� ---------------------------------------------------------------*/
Menu_Def gs_Menu = {0}; //Ŀ¼�˵�

/* ȫ�ֺ�����д ---------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @Function_Name : Menu_Init()     
* @Description   : �˵���ʼ��
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
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
        if( gs_Menu.Lock ==1)  gs_Switch.Magnet = 1;  //���������˵��²��ܳ��        
        Key_ResetFSM();  //������ϰ�������������������Ч              
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
* @Description   : �˵�����
* @Parameter     : void
* @Return        : void
* @Programer     : WindRises��л���죩
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


/*******************************(C) COPYRIGHT 2015 WindRises��л���죩*********************************/

