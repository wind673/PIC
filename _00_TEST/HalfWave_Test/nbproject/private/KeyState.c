/**********************************************************************************************
 *   �� �� ����KeyStste.c
 *
 *   ����ƽ̨��ǧ�������----�°�벨
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2012.12.13
 **********************************************************************************************/

/* ���� --------------------------------------------------------------------------------------*/
#include "KeyState.h"
/* ˽�к� ------------------------------------------------------------------------------------*/
#define LONG_KEY_COUNT  15    		//����������
#define KEY_SHIELD      0xfff0		//��Ҫ���εİ���IO��  16��������Ҫ�����ĸ�����ֻ��Ҫ����Ӧλ��1
/* ˽�б��� ----------------------------------------------------------------------------------*/
__Key_StateMachine Key_StateMachine_Local;
/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/* ˽�к������� ------------------------------------------------------------------------------*/
static void Key_Num_Get(__Key_StateMachine *Key_State);
/* ˽�к���ģ�� ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *��    �ƣ�void Key_State_Sweep(__Key_StateMachine *Key_State)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    ��������״̬��
 *********************************************************************************************/
void Key_State_Sweep(__Key_StateMachine *Key_State)
{
		Key_State->KeyCode_Pre =  ((uint16_t)PORTCbits.RC0<<0)
                                | ((uint16_t)PORTCbits.RC1<<1)
                                | ((uint16_t)PORTAbits.RA4<<2)
                                | ((uint16_t)PORTAbits.RA5<<3)|KEY_SHIELD;
		switch(Key_State->State_Flag)
		{
				case 0:
					if(Key_State->KeyCode_Pre != 0xffff)    //�ж��Ƿ��а�������
					{
							Key_State->State_Flag = 1;     			//�а�������������1��
								Key_State->KeyCode_Bef =  ((uint16_t)PORTCbits.RC0<<0)
                                                        | ((uint16_t)PORTCbits.RC1<<1)
                                                        | ((uint16_t)PORTAbits.RA4<<2)
                                                        | ((uint16_t)PORTAbits.RA5<<3)|KEY_SHIELD;
							Key_Num_Get(Key_State);
							Key_State->Key_Mode = 0;       			//�ް���
					}
					else
					{
							Key_State->State_Flag = 0;     			//�ް�����ͣ���ڵ�0��
							Key_State->Key_Mode = 0;       			//�ް���
					}
					break;
					
				case 1:
					if((Key_State->KeyCode_Pre != 0xffff) && 
						 (Key_State->KeyCode_Pre == Key_State->KeyCode_Bef))    //�ж��Ƿ��а������������ϼ����°�����ͬ
					{
							Key_State->Key_Mode = 0;       //�ް���
							Key_State->State_Flag = 1;     //ͣ���ڵ�1��
							Key_State->Key_Count++;        //������������1
							if(Key_State->Key_Count == 3)       //�жϳ�������������1
							{
									if(Key_State->Key_Num == 1)
									{
											Key_State->Key_Mode = 1;   //�����̰���
									}
									else if(Key_State->Key_Num > 1)
									{
											Key_State->Key_Mode = 2;   //��϶̰���
									}
							}
							if(Key_State->Key_Count == LONG_KEY_COUNT)       //�ж��Ƿ�ﵽ����������ֵ
							{
									if(!(Key_State->Key_Mode))
									{
											if(Key_State->Key_Num == 1)
											{
													Key_State->Key_Mode = 3;    //����������
											}
											else if(Key_State->Key_Num > 1)
											{
													Key_State->Key_Mode = 4;    //��ϳ�����
											}
									}
									Key_State->Key_Count = 0;                    //����������ֵ����
									Key_State->State_Flag = 2;                   //���㳤��������ֵ�������2��
							}
					}
					else
					{
							Key_State->Key_Count = 0;				 //����������ֵ����
							Key_State->State_Flag = 0;	     //���ص�0��
							Key_State->Key_Mode = 0;       	 //�ް���
					}
					break;
					
				case 2:
					if((Key_State->KeyCode_Pre != 0xffff) && 
						 (Key_State->KeyCode_Pre == Key_State->KeyCode_Bef))   //�ж��Ƿ��а������������ϼ����°�����ͬ
					{
							Key_State->State_Flag = 2; 										//ͣ���ڵ�2��
							if(Key_State->Key_Num == 1)
							{
									Key_State->Key_Mode = 5;    //������������
							}
							if(Key_State->Key_Num > 1)
							{
									Key_State->Key_Mode = 6;    //��ϳ�������
							}
					}
					else
					{
							Key_State->Key_Mode = 0;
							Key_State->State_Flag = 0;
							Key_State->Key_Count = 0;
					}
					break;
		}
}
/**********************************************************************************************
 *��    �ƣ�static void Key_Num_Get(__Key_StateMachine *Key_State)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    �������̼�ֵ��ȡ
 *********************************************************************************************/
static void Key_Num_Get(__Key_StateMachine *Key_State)
{
		uint8_t i;
		Key_State->Key_Num = 0;
		for(i = 0;i < 16;i++)
		{
				Key_State->Key_Num += !((Key_State->KeyCode_Bef >> i) & 0x0001); 
		}
}

/* �ļ����� ---------------------------------------------------------------------------------*/

