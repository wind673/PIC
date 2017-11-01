/**************************(c) Roon**Start File********************************/
/*=============================================================================
* File   Name : hal_usart.h
* Description : �ײ㴮�������ļ�
* Date        : 2015 - 09 - 16
* By          : �� ��
* E-mail      : roonmobi@126.com
* Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* Explain     :
*=============================================================================*/
/* ��ֹ�ݹ���� ---------------------------------------------------------------*/
#ifndef __HAL_USART_H_
#define __HAL_USART_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "main.h"
     
/* ˽�к궨�� -----------------------------------------------------------------*/
/* DE RE ����λ --------------------------------------------------- */
#define RS485_TX_EN()     PORTCbits.RC2 = 0
#define RS485_RX_EN()     PORTCbits.RC2 = 1
     
/* �������ݳ��� ��λbyte ------------------------------------------- */
#define RS485_DATALEN       10
     
#define _rn_EN_ALLINT()     INTCON |= 0x80				   /* ʹ��ȫ���ж�     */
#define _rn_DIS_ALLINT()	INTCON &= 0x7f				   /* ��ֹȫ���ж� 	  */
#define _rn_EN_PERINT()     INTCON |= 0x40				   /* ʹ�������ж�     */
#define _rn_DIS_PERINT()	INTCON &= 0xbf				   /* ��ֹ�����ж� 	  */
     
/* ˽�б������� ---------------------------------------------------------------*/
/* ��ַ���ֽ� ---------------------------------------------------------------- */
typedef enum
{
    act_Magnet_Success = 0X01,  //��ųɹ�
    act_Magnet_Warning,         //��ű���
    act_Demagnet_Success,       //�˴ųɹ�
    act_Demagnet_Warning,       //�˴ű���
} CBACTION_ENUM;
     
typedef enum
{
    add_ControlBoard = 0X01,    //����
    add_Panel,                  //���
    add_FarPanel,               //Զ�����
    add_Handle,                 //�ֱ�
    add_Sensor,                 //��������
} ADD_ENUM;

/* �������ֽ� ---------------------------------------------------------------- */
typedef enum
{
    cmd_PANEL_MAGNET = 0X01,   //�����
    cmd_PANEL_DEMAGNET,        //����˴�
    cmd_PANEL_SEARCH,          //����ѯ����
    cmd_PANEL_MODIFY = 0X04,   //����޸Ĳ���
} PANEL_CMD_ENUM;

typedef enum
{
    cmd_HANDLE_MAGNET = 0X05,   //�ֱ����
    cmd_HANDLE_DEMAGNET,        //�ֱ��˴�
    cmd_HANDLE_SEARCH,          //�ֱ���ѯ����
    cmd_HANDLE_MODIFY,          //�ֱ��޸Ĳ���
    cmd_HANDLE_MONITOR = 0X09,  //�ֱ����
} HANDLE_CMD_ENUM;

typedef enum
{
    cmd_FARPANEL_MAGNET = 0X0A,   //Զ�������
    cmd_FARPANEL_DEMAGNET,        //Զ������˴�
    cmd_FARPANEL_SEARCH,          //Զ������ѯ����
    cmd_FARPANEL_MODIFY = 0X0D,   //Զ������޸Ĳ���
} FARPANEL_CMD_ENUM;

typedef enum
{
    cmd_SENSOR_TILT_WAR = 0X0E,   //������б����
    cmd_SENSOR_WEIGH_WAR,         //���г��ؾ���
    cmd_SENSOR_WEIGH = 0X10,      //���г���
} FARPANEL_CMD_ENUM;

typedef enum
{
    cmd_CB_SUCCESS = 0X11,      //������˴ųɹ�
    cmd_CB_WARNING,             //������˴ž���
    cmd_CB_RETV_PARAM,          //���巵�ز���
    cmd_CB_RETS_PARAM,          //����Ĳγɹ�
    cmd_CB_RETV_MONITOR,        //���巵�ؼ������
} CB_CMD_ENUM;
     
/* �������Ͷ��� ---------------------------------------------------- */
typedef struct fram_t
{
    uint8_t ucRx_Buf[RS485_DATALEN];    //���ջ�����
    uint8_t ucTx_Buf[RS485_DATALEN];    //���ͻ�����
    uint8_t ucCnt;                      //�ֽڼ�����
    uint8_t ucFlg;                      //������λ
    uint32_t ulTime;                    //��ʱʱ��
} FRAM_T;

FRAM_T RS485Fram;
     
/* �������� -------------------------------------------------------------------*/
void RS485_halInit(void);

void Handle_PtlPackSend(ADD_ENUM _Add, HANDLE_CMD_ENUM _Cmd, uint8_t _ParamNo,\
                            uint16_t _ParamValue, uint8_t _Ch);

void RS485_ReceiveData(void);

void RS485_SendData(uint8_t *_pucBuf, uint8_t _ucLen);

void CB_ProtocolAnalysis(ADD_ENUM _Dev);

void Handle_ProtocolAnalysis(void);

#ifdef __cplusplus
}
#endif

#endif
/**************************(c) Roon**End File**********************************/
