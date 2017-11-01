/**********************************************************************************************
 *   �� �� ����ADC.c
 *
 *   ����ƽ̨��PIC18FXX ����ƽ̨
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2013.9.4
 **********************************************************************************************/
 
/* ���� --------------------------------------------------------------------------------------*/
#include "ADC.h"
/* ˽�к� ------------------------------------------------------------------------------------*/

/* ˽�б��� ----------------------------------------------------------------------------------*/
extern __Parameter Parameter[PARAM_NUM+1];
/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/* ˽�к������� ------------------------------------------------------------------------------*/

/* ˽�к���ģ�� ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *��    �ƣ�void ADC_Init(void)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    ����ADC��ʼ��
 *********************************************************************************************/
void ADC_Init(void)
{
    uint32_t elec = 0,i;
    OpenADC(ADC_RIGHT_JUST &
            ADC_4_TAD &
            ADC_FOSC_2,
            
            ADC_CH6,
            
            ADC_TRIG_CCP2 &
            ADC_REF_VDD_INT_VREF_4 &
            ADC_REF_VDD_VSS &          //���ο���ѹѡ��
            ADC_NEG_CH0                //ģ�⸺ͨ��ѡ��λ��һ��ѡ��ͨ��0--AVss��
            );
    ADC_INT_DISABLE();                 //��ADC�ж�
	for(i = 0;i < 5;i++)
	{
		ConvertADC();
        while(BusyADC());
		elec += ReadADC();
	}
	Parameter[_ELEC_SETOVER].Value = elec/5;
}

/**********************************************************************************************
 *��    �ƣ�uint16_t ADC_ElecGet(void)
 *
 *��    ������
 *
 *�� �� ֵ��uint16_t elec   ��������ֵ
 *
 *��    ������������
 *********************************************************************************************/
uint16_t ADC_ElecGet(void)
{
	uint32_t elec = 0,i;
	for(i = 0;i < 5;i++)
	{
		ConvertADC();
        while(BusyADC());
		elec += ReadADC();
	}
	elec = elec/5;
	if(elec > Parameter[_ELEC_SETOVER].Value)
		elec = (elec-Parameter[_ELEC_SETOVER].Value)/Parameter[_ELEC_COEFF].Value;
	else
		elec = (Parameter[_ELEC_SETOVER].Value - elec)/Parameter[_ELEC_COEFF].Value;
	return elec;
}
/* �ļ����� ---------------------------------------------------------------------------------*/



