/**********************************************************************************************
 *   文 件 名：triac.c
 *
 *   调试平台：千豪电磁铁----新版半波调试板
 *
 *   作    者：唐 江
 *
 *   日    期：2015.10.8
 **********************************************************************************************/

/* 包含 --------------------------------------------------------------------------------------*/
#include "triac.h"
/* 私有宏 ------------------------------------------------------------------------------------*/

/* 私有变量 ----------------------------------------------------------------------------------*/
extern __Parameter Parameter[PARAM_NUM+1];
extern volatile uint32_t Message;
extern uint16_t Spacing_Count;
uint16_t Elec_Max[40];
volatile uint8_t Elec[16][40];  //每个通道电流记录
uint16_t Houwa_Cuont = 0;
uint8_t Magnet_Flag = 1,Demag_Flag = 1;
uint16_t Gears_Timer[16] = {8000,7500,7050,6650,6250,5850,5500,5150,4750,
                                     4350,4000,3500,2750,2000,1250,500};
/* 私有结构体 --------------------------------------------------------------------------------*/

/* 私有函数声明 ------------------------------------------------------------------------------*/
static void Trica_Control(EMCC_State EMCC_State);
/* 私有函数模型 ------------------------------------------------------------------------------*/
/**********************************************************************************************
 *名    称：static u8 Trica_Mag(EMCC_State EMCC_State)
 *
 *参    数： \param  EMCC_State EMCC_State   充退磁状态
 *                   MAGNET  充磁
 *                   DEMAG   退磁
 *
 *返 回 值：无
 *
 *描    述：充退磁启动函数
 *********************************************************************************************/
static uint8_t Trica_Mag(EMCC_State EMCC_State)
{
	uint16_t Elec = 0;
	uint16_t i=0,j,k;
	Houwa_Cuont = 0;
	for(j = 0;j < 40;j++)
	{
		Elec_Max[j]  = 0;
	}
/* 充磁 -------------------------------------------------------------------------------------------*/
	if(EMCC_State == MAGNET)   //充磁
	{
			if(Parameter[_LOAD_INVERT].Value)
			{
					for(i = 0; i < Parameter[_PULSE].Value*2; i++)
					{
							while(TRIAC_ACPLS_PORT == 0);  //滤掉一个负半波
							while(TRIAC_ACPLS_PORT == 1);  //滤掉一个正半波
							delay_us(Gears_Timer[Parameter[_GEARS_MAGNE].Value]);  //档位延时启动...
							Trica_Control(MAGNET);              //启动可控硅导通
							while(TRIAC_ACPLS_PORT == 0)
							{
									Elec = ADC_ElecGet();
									if(Elec_Max[i] < Elec && Elec <= 1000)
										Elec_Max[i] = Elec;     //获取电流最大值
									if(Elec > Parameter[_ELEC_MAX].Value*10)       //大于电流最大值
										return 0;
							}
							if(Elec_Max[i] >= Parameter[_MAGNET_ELEC_THRE].Value*10)
								++Houwa_Cuont;
							if(Houwa_Cuont == Parameter[_PULSE_THRE].Value)
								return 1;
							for(k = Parameter[_PULSE_SPACING].Value*2;k > 0;k--)
							{
								while(TRIAC_ACPLS_PORT == 0);  //滤掉一个负半波
								while(TRIAC_ACPLS_PORT == 1);  //滤掉一个正半波
							}
					}
					if(Elec_Max[i-1] < Parameter[_ELEC_MIN].Value*10)  //小于电流最小值
								return 0;
			}
			else
			{
					for(i = 0; i < Parameter[_PULSE].Value*2; i++)
					{
							while(TRIAC_ACPLS_PORT == 0);  //滤掉一个负半波
							while(TRIAC_ACPLS_PORT == 1);  //滤掉一个正半波
							delay_us(Gears_Timer[Parameter[_GEARS_MAGNE].Value]);  //档位延时启动...
							Trica_Control(DEMAG);              //启动可控硅导通
							while(TRIAC_ACPLS_PORT == 0)
							{
									Elec = ADC_ElecGet();
									if(Elec_Max[i] < Elec && Elec <= 1000)
										Elec_Max[i] = Elec;     //获取电流最大值
									if(Elec > Parameter[_ELEC_MAX].Value*10)       //大于电流最大值
										return 0;
							}
							if(Elec_Max[i] >= Parameter[_MAGNET_ELEC_THRE].Value*10)
								++Houwa_Cuont;
							if(Houwa_Cuont == Parameter[_PULSE_THRE].Value)
								return 1;
							for(k = Parameter[_PULSE_SPACING].Value*2;k > 0;k--)
							{
								while(TRIAC_ACPLS_PORT == 0);  //滤掉一个负半波
								while(TRIAC_ACPLS_PORT == 1);  //滤掉一个正半波
							}
					}
					if(Elec_Max[i-1] < Parameter[_ELEC_MIN].Value*10)  //小于电流最小值
								return 0;
			}
	}
/* 退磁 -------------------------------------------------------------------------------------------*/
	else if(EMCC_State == DEMAG)   //退磁
	{
		if(Parameter[_LOAD_INVERT].Value)
		{
				for(i = 0; i < Parameter[_PULSE].Value*2; i++)
				{
					while(TRIAC_ACPLS_PORT == 0);  //滤掉一个负半波
					while(TRIAC_ACPLS_PORT == 1);  //滤掉一个正半波
					delay_us(Gears_Timer[Parameter[_GEARS_MAGNE].Value]);  //档位延时启动...
					Trica_Control(DEMAG);              //启动可控硅导通
					while(TRIAC_ACPLS_PORT == 0)
					{
						Elec = ADC_ElecGet();
						if(Elec_Max[i] < Elec && Elec <= 1000)
							Elec_Max[i] = Elec;     //获取电流最大值
						if(Elec > Parameter[_ELEC_MAX].Value*10)       //大于电流最大值
							return 0;
					}
					if(Elec_Max[i] >= Parameter[_MAGNET_ELEC_THRE].Value*10)
						++Houwa_Cuont;
					if(Houwa_Cuont == Parameter[_PULSE_THRE].Value)
						return 1;
					for(k = Parameter[_PULSE_SPACING].Value*2;k > 0;k--)
					{
						while(TRIAC_ACPLS_PORT == 0);  //滤掉一个负半波
						while(TRIAC_ACPLS_PORT == 1);  //滤掉一个正半波
					}
				}
				if(Elec_Max[i-1] < Parameter[_ELEC_MIN].Value*10)  //小于电流最小值
							return 0;
		}
		else
		{
				for(i = 0; i < Parameter[_PULSE].Value*2; i++)
					{
							while(TRIAC_ACPLS_PORT == 0);  //滤掉一个负半波
							while(TRIAC_ACPLS_PORT == 1);  //滤掉一个正半波
							delay_us(Gears_Timer[Parameter[_GEARS_MAGNE].Value]);  //档位延时启动...
							Trica_Control(MAGNET);              //启动可控硅导通
							while(TRIAC_ACPLS_PORT == 0)
							{
									Elec = ADC_ElecGet();
									if(Elec_Max[i] < Elec && Elec <= 1000)
										Elec_Max[i] = Elec;     //获取电流最大值
									if(Elec > Parameter[_ELEC_MAX].Value*10)       //大于电流最大值
										return 0;
							}
							if(Elec_Max[i] >= Parameter[_MAGNET_ELEC_THRE].Value*10)
								++Houwa_Cuont;
							if(Houwa_Cuont == Parameter[_PULSE_THRE].Value)
								return 1;
							for(k = Parameter[_PULSE_SPACING].Value*2;k > 0;k--)
							{
								while(TRIAC_ACPLS_PORT == 0);  //滤掉一个负半波
								while(TRIAC_ACPLS_PORT == 1);  //滤掉一个正半波
							}
					}
				if(Elec_Max[i-1] < Parameter[_ELEC_MIN].Value*10)  //小于电流最小值
							return 0;
		}
	}
	return 0;
}
 
/*********************************************************************************************
 *名    称：void Trica_Control(EMCC_State EMCC_State)
 *
 *参    数： \param  EMCC_State EMCC_State   充退磁状态
 *                   MAGNET  充磁
 *                   DEMAG   退磁
 *
 *返 回 值：无
 *
 *描    述：可控硅控制
 *********************************************************************************************/
static void Trica_Control(EMCC_State EMCC_State)
{
	uint8_t i;
	if(EMCC_State == DEMAG)
	{
		for(i = 1; i <= 6; i++)
		{
			TRIAC_MAGNET_PORT = 1;
			delay_us(100);
			TRIAC_MAGNET_PORT = 0;
			delay_us(200);
		}
		TRIAC_MAGNET_PORT = 0;
		}
		else if(EMCC_State == MAGNET)
		{
			for(i = 1; i <= 6; i++)
			{
				TRIAC_DEMAG_PORT = 1;
				delay_us(100);
				TRIAC_DEMAG_PORT = 0;
				delay_us(200);
			}
			TRIAC_DEMAG_PORT = 0;
		}
}
/**********************************************************************************************
 *名    称：void Magne_Demag_Dispose(EMCC_State EMCC_State)
 *
 *参    数：EMCC_State EMCC_State   充退磁选择
 *
 *返 回 值：无
 *
 *描    述：充退磁处理
 *********************************************************************************************/
void Magne_Demag_Dispose(EMCC_State EMCC_State)
{
	uint8_t i,j;
	if(EMCC_State == MAGNET)
	{
			Message &= ~MESSAGE_MAGNET_WARN;
			Message &= ~MESSAGE_DEMAGE_WARN;
			if(Parameter[_CHANNEL_SW].Value > 0)
			{
				Relay_COM_ON;
                //EXIT_DIS;
			}
			for(i = 0; i < 16; i++)
			{
					Magnet_Flag = 1;
					if((Parameter[_CHANNEL_SW].Value >> i)&(uint16_t)1)
					{
							delay_ms(200);
							Relay_Channel_SW(i+1,ENABLE);
							Magnet_Flag = Trica_Mag(MAGNET);
							delay_ms(200);
							Relay_Channel_SW(i+1,DISABLE);
							for(j = 0;j < 40; j++)
							{
								Elec[i][j] = (uint8_t)((Elec_Max[j]+9)/10);
							}
							//I2C_EE_Write_16Bits_Data(Elec_Max,80*i,Houwa_Cuont);
					}
					if(Magnet_Flag && !(Message & MESSAGE_MAGNET_WARN))
					{
						Message |= MESSAGE_MAGNET_FINISH;
						Message &= ~MESSAGE_DEMAGE_FINISH;
						Message &= ~MESSAGE_MAGNET_WARN;
					}
					else
					{
						Message |= MESSAGE_MAGNET_WARN;
						Message &= ~MESSAGE_MAGNET_FINISH;
						Message &= ~MESSAGE_DEMAGE_FINISH;
					}
			}
			delay_ms(200);
			Relay_COM_OFF;
			//EXIT_EN;
			delay_ms(200);
	}
	else if(EMCC_State == DEMAG)
	{
			Message &= ~MESSAGE_DEMAGE_WARN;
			Message &= ~MESSAGE_MAGNET_WARN;
			if(Parameter[_CHANNEL_SW].Value > 0)
			{
				Relay_COM_ON;
				//EXIT_DIS;
			}
			for(i = 0; i < 16; i++)
			{
					Demag_Flag = 1;
					if((Parameter[_CHANNEL_SW].Value >> i)&(uint16_t)1)
					{
							delay_ms(200);
							Relay_Channel_SW(i+1,ENABLE);
							Demag_Flag = Trica_Mag(DEMAG);
							delay_ms(200);
							Relay_Channel_SW(i+1,DISABLE);		
							
							for(j = 0;j < 40; j++)
							{
								Elec[i][j] = (uint8_t)((Elec_Max[j]+9)/10);
							}
							//I2C_EE_Write_16Bits_Data(Elec_Max,80*i,Houwa_Cuont);
					}
					if(Demag_Flag && !(Message & MESSAGE_DEMAGE_WARN))
					{
						Message |= MESSAGE_DEMAGE_FINISH;
						Message &= ~MESSAGE_MAGNET_FINISH;
						Message &= ~MESSAGE_DEMAGE_WARN;
					}
					else
					{
						Message |= MESSAGE_DEMAGE_WARN;
						Message &= ~MESSAGE_DEMAGE_FINISH;
						Message &= ~MESSAGE_MAGNET_FINISH;
					}
			}
			delay_ms(200);
			Relay_COM_OFF;
			//EXIT_EN;
			delay_ms(200);
	}
	Spacing_Count = Parameter[_OPERATE_SPACING].Value*50;
}

/**********************************************************************************************
 *名    称：void Relay_Channel_SW(uint8_t Channel,FunctionalState Flag)
 *
 *参    数：uint8_t Channel        通道选择
 *          FunctionalState Flag   开关状态
 *         
 *返 回 值：无
 *
 *描    述：充退磁处理
 *********************************************************************************************/
void Relay_Channel_SW(uint8_t Channel,FunctionalState Flag)
{
	switch(Channel)
	{
		case 1:
			if(Flag)
			{
				Relay_Channel_1_ON;
			}
			else
			{
				Relay_Channel_1_OFF;
			}
			break;
		
		case 2:
			if(Flag)
			{
				Relay_Channel_2_ON;
			}
			else
			{
				Relay_Channel_2_OFF;
			}
			break;
		
		case 3:
			if(Flag)
			{
				PORTEbits.RE2 = 1;
			}
			else
			{
				PORTEbits.RE2 = 0;
			}
			break;
		
		case 4:
			if(Flag)
			{
				PORTEbits.RE3 = 1;
			}
			else
			{
				PORTEbits.RE3 = 0;
			}
			break;
		
		case 5:
			if(Flag)
			{
				PORTEbits.RE4 = 1;
			}
			else
			{
				PORTEbits.RE4 = 0;
			}
			break;
		
		case 6:
			if(Flag)
			{
				PORTEbits.RE5 = 1;
			}
			else
			{
				PORTEbits.RE5 = 0;
			}
			break;
		
		case 7:
			if(Flag)
			{
				PORTEbits.RE6 = 1;
			}
			else
			{
				PORTEbits.RE6 = 0;
			}
			break;
		
		case 8:
			if(Flag)
			{
				PORTEbits.RE7 = 1;
			}
			else
			{
				PORTEbits.RE7 = 0;
			}
			break;
		/*
		case 9:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X10,PCF8575_Write_Add_2);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_2);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X20,PCF8575_Write_Add_2);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_2);
			}
			break;
		
		case 10:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X40,PCF8575_Write_Add_2);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_2);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X80,PCF8575_Write_Add_2);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_2);
			}
			break;
		case 11:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X01,0X00,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			else
			{
				PCF8575_Relay_Drive(0X02,0X00,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			break;
		
		case 12:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X04,0X00,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			else
			{
				PCF8575_Relay_Drive(0X08,0X00,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			break;
		
		case 13:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X10,0X00,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			else
			{
				PCF8575_Relay_Drive(0X20,0X00,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			break;
		
		case 14:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X40,0X00,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			else
			{
				PCF8575_Relay_Drive(0X80,0X00,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			break;
		
		case 15:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X01,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X02,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			break;
		
		case 16:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X04,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X08,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			break;
	 
		case 17:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X10,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X20,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			break;
		
		case 18:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X40,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X80,PCF8575_Write_Add_3);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_3);
			}
			break;
			
		case 19:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X01,0X00,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			else
			{
				PCF8575_Relay_Drive(0X02,0X00,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			break;
		
		case 20:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X04,0X00,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			else
			{
				PCF8575_Relay_Drive(0X08,0X00,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			break;
		
		case 21:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X10,0X00,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			else
			{
				PCF8575_Relay_Drive(0X20,0X00,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			break;
		
		case 22:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X40,0X00,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			else
			{
				PCF8575_Relay_Drive(0X80,0X00,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			break;
		
		case 23:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X01,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X02,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			break;
		
		case 24:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X04,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X08,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			break;
		
		case 25:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X10,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X20,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			break;
		
		case 26:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X40,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X80,PCF8575_Write_Add_4);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_4);
			}
			break;
			
		case 27:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X01,0X00,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			else
			{
				PCF8575_Relay_Drive(0X02,0X00,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			break;
		
		case 28:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X04,0X00,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			else
			{
				PCF8575_Relay_Drive(0X08,0X00,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			break;
		
		case 29:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X10,0X00,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			else
			{
				PCF8575_Relay_Drive(0X20,0X00,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			break;
		
		case 30:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X40,0X00,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			else
			{
				PCF8575_Relay_Drive(0X80,0X00,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			break;
		
		case 31:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X01,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X02,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			break;
		
		case 32:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X04,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X08,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			break;
		
		case 33:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X10,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X20,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			break;
		
		case 34:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X40,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X80,PCF8575_Write_Add_5);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_5);
			}
			break;
			
		case 35:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X01,0X00,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			else
			{
				PCF8575_Relay_Drive(0X02,0X00,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			break;
		
		case 36:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X04,0X00,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			else
			{
				PCF8575_Relay_Drive(0X08,0X00,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			break;
		
		case 37:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X10,0X00,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			else
			{
				PCF8575_Relay_Drive(0X20,0X00,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			break;
		
		case 38:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X40,0X00,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			else
			{
				PCF8575_Relay_Drive(0X80,0X00,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			break;
		
		case 39:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X01,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X02,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			break;
		
		case 40:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X04,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X08,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			break;
		
		case 41:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X10,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X20,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			break;
		
		case 42:
			if(Flag)
			{
				PCF8575_Relay_Drive(0X00,0X40,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			else
			{
				PCF8575_Relay_Drive(0X00,0X80,PCF8575_Write_Add_6);
				delay_ms(60);
				PCF8575_Relay_Drive(0X00,0X00,PCF8575_Write_Add_6);
			}
			break;
		*/
		default:
			break;
	}
}
/* 文件结束 ---------------------------------------------------------------------------------*/



