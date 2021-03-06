/**********************************************************************************************
 *   文 件 名：pic18f67xx_it.c
 *
 *   调试平台：PIC18FXX 开发平台
 *
 *   作    者：唐 江
 *
 *   日    期：2013.10.8
 **********************************************************************************************/
 
/* 包含 --------------------------------------------------------------------------------------*/
#include "pic18f67xx_it.h"
#include "hal_Usart.h"
/* 私有宏 ------------------------------------------------------------------------------------*/

/* 私有变量 ----------------------------------------------------------------------------------*/
uint16_t Spacing_Count = 0;
extern __Key_StateMachine Key_StateMachine_Local;
/* 私有结构体 --------------------------------------------------------------------------------*/

/* 私有函数声明 ------------------------------------------------------------------------------*/

/* 私有函数模型 ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *名    称：void interrupt timer0(void)
 *
 *参    数： 无
 *
 *返 回 值：无
 *
 *描    述： 中断服务函数
 *********************************************************************************************/
void interrupt ISR(void)
{
    if(TMR0IF == 1)  
    {
        TMR0IF = 0;
        WriteTimer0(65536-50000);              //重载初始值
        if(Spacing_Count)
            Spacing_Count--;
        Key_State_Sweep(&Key_StateMachine_Local);
    }
//    else if(ADIF == 1)
//    {
//        ADIF = 0;
//    }
/* 串口1接收中断 ------------------------------------------------------------- */
    if(RC1IF == 1)
    {
        RS485Fram.ucRx_Buf[RS485Fram.ucCnt] = RCREG1;
        if (RS485Fram.ucCnt == (RS485_DATALEN - 1))
        {
            RS485Fram.ucFlg = 1;
        }
        else
        {
            RS485Fram.ucCnt++;
        }
    }
}

/* 文件结束 ---------------------------------------------------------------------------------*/


