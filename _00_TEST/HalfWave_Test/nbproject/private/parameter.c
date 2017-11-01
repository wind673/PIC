/**********************************************************************************************
 *   文 件 名：parameter.c
 *
 *   调试平台：千豪电磁铁----新版半波调试板
 *
 *   作    者：唐 江
 *
 *   日    期：2014.12.12
 **********************************************************************************************/

/* 包含 --------------------------------------------------------------------------------------*/
#include "parameter.h"
#include "string.h"
/* 私有宏 ------------------------------------------------------------------------------------*/

/* 私有变量 ----------------------------------------------------------------------------------*/
//extern uint16_t Param_Buff[1024];
__Parameter Parameter[PARAM_NUM+1];
/* 私有结构体 --------------------------------------------------------------------------------*/

/* 私有函数声明 ------------------------------------------------------------------------------*/

/* 私有函数模型 ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *名    称：void Parameter_Init(void)
 *
 *参    数：无
 *
 *返 回 值：无
 *
 *描    述：系统参数初始化
 *********************************************************************************************/
void Parameter_Init(void)
{
		uint8_t i;
/* 充磁档位 ---------------------------------------------------------------------------------*/
		Parameter[_GEARS_MAGNE].Min = 0; 
		Parameter[_GEARS_MAGNE].Max = 15; 
		Parameter[_GEARS_MAGNE].Default  = 15;
/* 退磁档位 ---------------------------------------------------------------------------------*/
		Parameter[_GEARS_DEMAG].Min = 0; 
		Parameter[_GEARS_DEMAG].Max = 15; 
		Parameter[_GEARS_DEMAG].Default  = 15;
/* 通道使能 ---------------------------------------------------------------------------------*/
		Parameter[_CHANNEL_SW].Min = 0;
		Parameter[_CHANNEL_SW].Max = 0xffff;
		Parameter[_CHANNEL_SW].Default  = 0x00ff;
/* 电流偏置 ---------------------------------------------------------------------------------*/
		Parameter[_ELEC_SETOVER].Min = 100;
		Parameter[_ELEC_SETOVER].Max = 3000;
		Parameter[_ELEC_SETOVER].Default  = 2045;
/* 电流传感器系数 ---------------------------------------------------------------------------*/
		Parameter[_ELEC_COEFF].Min = 10;
		Parameter[_ELEC_COEFF].Max = 80;
		Parameter[_ELEC_COEFF].Default  = 20;
/* 充退磁脉冲个数 ---------------------------------------------------------------------------*/
		Parameter[_PULSE].Min = 20;
		Parameter[_PULSE].Max = 40;
		Parameter[_PULSE].Default  = 20;
/* 本体负载反相 -----------------------------------------------------------------------------*/
		Parameter[_LOAD_INVERT].Min = 0;
		Parameter[_LOAD_INVERT].Max = 1;
		Parameter[_LOAD_INVERT].Default  = 1;
/* 充退磁电流最小值 -------------------------------------------------------------------------*/
		Parameter[_ELEC_MIN].Min = 3;
		Parameter[_ELEC_MIN].Max = 200;
		Parameter[_ELEC_MIN].Default  = 10;
/* 充退磁电流最大值 -------------------------------------------------------------------------*/
		Parameter[_ELEC_MAX].Min = 3;
		Parameter[_ELEC_MAX].Max = 200;
		Parameter[_ELEC_MAX].Default  = 65;
/* 充磁饱和电流阀值 -------------------------------------------------------------------------*/
		Parameter[_MAGNET_ELEC_THRE].Min = 3;
		Parameter[_MAGNET_ELEC_THRE].Max = 200;
		Parameter[_MAGNET_ELEC_THRE].Default  = 10;
/* 退磁饱和电流阀值 -------------------------------------------------------------------------*/
		Parameter[_DEMAG_ELEC_THRE].Min = 3;
		Parameter[_DEMAG_ELEC_THRE].Max = 200;
		Parameter[_DEMAG_ELEC_THRE].Default  = 10;
/* 退磁方式选择 -----------------------------------------------------------------------------*/
		Parameter[_DEMAG_MODE].Min = 0;
		Parameter[_DEMAG_MODE].Max = 1;
		Parameter[_DEMAG_MODE].Default  = 1;
/* 连续操作时间间隔 -------------------------------------------------------------------------*/
		Parameter[_OPERATE_SPACING].Min = 1;
		Parameter[_OPERATE_SPACING].Max = 20;
		Parameter[_OPERATE_SPACING].Default  = 3;
/* 充退磁饱和脉冲个数 -----------------------------------------------------------------------*/	
		Parameter[_PULSE_THRE].Min = 3;
		Parameter[_PULSE_THRE].Max = 15;
		Parameter[_PULSE_THRE].Default  = 3;
/* 充退磁脉冲间隔 ---------------------------------------------------------------------------*/	
		Parameter[_PULSE_SPACING].Min = 0;
		Parameter[_PULSE_SPACING].Max = 15;
		Parameter[_PULSE_SPACING].Default  = 0;
/* PLC按键模式选择 --------------------------------------------------------------------------*/		
		Parameter[_PLC_KEY_MODE].Min = 0;
		Parameter[_PLC_KEY_MODE].Max = 1;
		Parameter[_PLC_KEY_MODE].Default  = 0;
		
		//FLash_ReadBuff_16(0,Param_Buff,1024);
		for(i = 1;i < PARAM_NUM+1;i++)
		{
            Parameter[i].Value = Parameter[i].Default;
//				if(Param_Buff[i] >= Parameter[i].Min && Param_Buff[i] <= Parameter[i].Max)
//				{
//						Parameter[i].Value = Param_Buff[i];
//				}
//				else
//				{
//						Parameter[i].Value = Parameter[i].Default;
//						//Flash_WriteBuff_16(i,&Parameter[i].Value,1);
//				}
		}
}
/* 文件结束 ---------------------------------------------------------------------------------*/



