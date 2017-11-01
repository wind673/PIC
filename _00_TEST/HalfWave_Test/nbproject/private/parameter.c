/**********************************************************************************************
 *   �� �� ����parameter.c
 *
 *   ����ƽ̨��ǧ�������----�°�벨���԰�
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2014.12.12
 **********************************************************************************************/

/* ���� --------------------------------------------------------------------------------------*/
#include "parameter.h"
#include "string.h"
/* ˽�к� ------------------------------------------------------------------------------------*/

/* ˽�б��� ----------------------------------------------------------------------------------*/
//extern uint16_t Param_Buff[1024];
__Parameter Parameter[PARAM_NUM+1];
/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/* ˽�к������� ------------------------------------------------------------------------------*/

/* ˽�к���ģ�� ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *��    �ƣ�void Parameter_Init(void)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    ����ϵͳ������ʼ��
 *********************************************************************************************/
void Parameter_Init(void)
{
		uint8_t i;
/* ��ŵ�λ ---------------------------------------------------------------------------------*/
		Parameter[_GEARS_MAGNE].Min = 0; 
		Parameter[_GEARS_MAGNE].Max = 15; 
		Parameter[_GEARS_MAGNE].Default  = 15;
/* �˴ŵ�λ ---------------------------------------------------------------------------------*/
		Parameter[_GEARS_DEMAG].Min = 0; 
		Parameter[_GEARS_DEMAG].Max = 15; 
		Parameter[_GEARS_DEMAG].Default  = 15;
/* ͨ��ʹ�� ---------------------------------------------------------------------------------*/
		Parameter[_CHANNEL_SW].Min = 0;
		Parameter[_CHANNEL_SW].Max = 0xffff;
		Parameter[_CHANNEL_SW].Default  = 0x00ff;
/* ����ƫ�� ---------------------------------------------------------------------------------*/
		Parameter[_ELEC_SETOVER].Min = 100;
		Parameter[_ELEC_SETOVER].Max = 3000;
		Parameter[_ELEC_SETOVER].Default  = 2045;
/* ����������ϵ�� ---------------------------------------------------------------------------*/
		Parameter[_ELEC_COEFF].Min = 10;
		Parameter[_ELEC_COEFF].Max = 80;
		Parameter[_ELEC_COEFF].Default  = 20;
/* ���˴�������� ---------------------------------------------------------------------------*/
		Parameter[_PULSE].Min = 20;
		Parameter[_PULSE].Max = 40;
		Parameter[_PULSE].Default  = 20;
/* ���帺�ط��� -----------------------------------------------------------------------------*/
		Parameter[_LOAD_INVERT].Min = 0;
		Parameter[_LOAD_INVERT].Max = 1;
		Parameter[_LOAD_INVERT].Default  = 1;
/* ���˴ŵ�����Сֵ -------------------------------------------------------------------------*/
		Parameter[_ELEC_MIN].Min = 3;
		Parameter[_ELEC_MIN].Max = 200;
		Parameter[_ELEC_MIN].Default  = 10;
/* ���˴ŵ������ֵ -------------------------------------------------------------------------*/
		Parameter[_ELEC_MAX].Min = 3;
		Parameter[_ELEC_MAX].Max = 200;
		Parameter[_ELEC_MAX].Default  = 65;
/* ��ű��͵�����ֵ -------------------------------------------------------------------------*/
		Parameter[_MAGNET_ELEC_THRE].Min = 3;
		Parameter[_MAGNET_ELEC_THRE].Max = 200;
		Parameter[_MAGNET_ELEC_THRE].Default  = 10;
/* �˴ű��͵�����ֵ -------------------------------------------------------------------------*/
		Parameter[_DEMAG_ELEC_THRE].Min = 3;
		Parameter[_DEMAG_ELEC_THRE].Max = 200;
		Parameter[_DEMAG_ELEC_THRE].Default  = 10;
/* �˴ŷ�ʽѡ�� -----------------------------------------------------------------------------*/
		Parameter[_DEMAG_MODE].Min = 0;
		Parameter[_DEMAG_MODE].Max = 1;
		Parameter[_DEMAG_MODE].Default  = 1;
/* ��������ʱ���� -------------------------------------------------------------------------*/
		Parameter[_OPERATE_SPACING].Min = 1;
		Parameter[_OPERATE_SPACING].Max = 20;
		Parameter[_OPERATE_SPACING].Default  = 3;
/* ���˴ű���������� -----------------------------------------------------------------------*/	
		Parameter[_PULSE_THRE].Min = 3;
		Parameter[_PULSE_THRE].Max = 15;
		Parameter[_PULSE_THRE].Default  = 3;
/* ���˴������� ---------------------------------------------------------------------------*/	
		Parameter[_PULSE_SPACING].Min = 0;
		Parameter[_PULSE_SPACING].Max = 15;
		Parameter[_PULSE_SPACING].Default  = 0;
/* PLC����ģʽѡ�� --------------------------------------------------------------------------*/		
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
/* �ļ����� ---------------------------------------------------------------------------------*/



