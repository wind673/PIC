/**************************(c) Roon**Start File********************************/
/*=============================================================================
* File   Name : hal_Usart.c
* Description : �ײ㴮�������ļ�
* Date        : 2015 - 10 - 08
* By          : �� ��
* E-mail      : roonmobi@126.com
* Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* Explain     :
*=============================================================================*/

/* ͷ�ļ����� -----------------------------------------------------------------*/
#include "hal_Usart.h"

/* ˽�к궨�� -----------------------------------------------------------------*/
/* ������ַѡ�� 1Ϊѡ�� 0��ѡ�� ------------------------------------------------*/
#define def_Local_ControlBoard          1
#define def_Local_Panel                 0
#define def_Local_FarPanel              0
#define def_Local_Handle                0
#define def_Local_Sensor                0

#if def_Local_ControlBoard == 1
    #define def_LocalAdd                0X01
#elif def_Local_Panel == 1
    #define def_LocalAdd                0X02
#elif def_Local_FarPanel == 1
    #define def_LocalAdd                0X03
#elif def_Local_Handle == 1
    #define def_LocalAdd                0X04
#elif def_Local_Sensor == 1
    #define def_LocalAdd                0X05
#endif

/* CRC16 ����ʽ */
#define def_CRC_16_POLYNOMIAL           0X1021  //0X8005

/* ֡ͷ���� */
#define def_FrameHead                   0XAA

/* ˽�б������� ---------------------------------------------------------------*/
extern volatile uint16_t g_usSysTestCnt;
extern volatile uint32_t Message;
extern __Parameter Parameter[PARAM_NUM+1];

volatile uint8_t g_ucMagFlg = 0;

/* ��̬�������� ---------------------------------------------------------------*/
static uint8_t RS485_MatchCorrect(void);
//static void RS485_ProtocolAnalysis(void);
static void Crc16(uint8_t *_pucBuf, uint16_t _usLen, uint8_t *_ucHBuye, uint8_t *_ucLByte);

/* ������д -------------------------------------------------------------------*/
/******************************************************************************
* Name        :		       RS485_halInit()
* Description : ����������ʼ������
* Parameter   : void
*
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 -04 / ���α�д
* Explain     : None
*******************************************************************************/
void RS485_halInit(void)
{
    /* �������� 9600������ */
    Open1USART( USART_TX_INT_OFF &
                USART_RX_INT_ON &
                USART_ASYNCH_MODE &
                USART_EIGHT_BIT &
                USART_CONT_RX &
                USART_BRGH_LOW,
                51);
    
    /* 485ģʽ���� GPIO ��ʼ�� */
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC7 = 1;
 //    ANCON2 &= 0XF9;
    
    /* ���ж� */
    _rn_EN_ALLINT();
    _rn_EN_PERINT();
    
    /* RS485���ڽ���ģʽ */
    RS485_RX_EN();
}


#if def_Local_Handle == 1
/******************************************************************************
* Name        :             RS485_ReceiveData(void)
* Description : 485�������ݺ���
* Parameter   : void
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 - 26 / ���α�д
* Explain     : None
*******************************************************************************/
void RS485_ReceiveData(void)
{
    if (RS485Fram.ucFlg)
    {
        RS485Fram.ucFlg = 0;
        RS485Fram.ucCnt = 0;
        Handle_ProtocolAnalysis();
    }
}


/******************************************************************************
* Name        : Handle_PtlPackSend(ADD_ENUM _Add, HANDLE_CMD_ENUM _Cmd, uint8_t _ParamNo,\
*                                   uint16_t _ParamValue, uint8_t _Ch)
* Description : �ֱ�Э�������
* Parameter   : ADD_ENUM _Add           ��ַ��
*               HANDLE_CMD_ENUM _Cmd    ������
*               uint8_t _ParamNo        �������
*               uint16_t _ParamValue    ����ֵ
*               uint8_t _Ch             ͨ��
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 08 / ���α�д
* Explain     : �����Э��ο��ļ�
*******************************************************************************/
void Handle_PtlPackSend(ADD_ENUM _Add, HANDLE_CMD_ENUM _Cmd, uint8_t _ParamNo,\
                            uint16_t _ParamValue, uint8_t _Ch)
{
    uint8_t uci;
    uint8_t ucHByte,ucLByte;
    
/* װ�س�ֵ ------------------------------------------------------------------ */
    RS485Fram.ucTx_Buf[0] = def_FrameHead;
    RS485Fram.ucTx_Buf[1] = _Add;
    RS485Fram.ucTx_Buf[2] = _Cmd;
    for (uci = 3; uci < RS485_DATALEN; uci++)
    {
        RS485Fram.ucTx_Buf[uci] = 0X55;
    }
    uci = 3;
    
/* ������װ�� ---------------------------------------------------------------- */
    /* �ֱ���ѯ���� */
    if (_Cmd == cmd_HANDLE_SEARCH)
    {
        RS485Fram.ucTx_Buf[uci++] = _ParamNo;
    }
    /* �ֱ��޸����� */
    else if (_Cmd == cmd_HANDLE_MODIFY)
    {
        RS485Fram.ucTx_Buf[uci++] = _ParamNo;
        RS485Fram.ucTx_Buf[uci++] = (uint8_t)(_ParamValue >> 8);
        RS485Fram.ucTx_Buf[uci++] = (uint8_t)(_ParamValue);
    }
    /* �ֱ�������� */
    else if (_Cmd == cmd_HANDLE_MONITOR)
    {
        RS485Fram.ucTx_Buf[uci++] = _Ch;
    }
    
/* У����װ�� ---------------------------------------------------------------- */
    Crc16(RS485Fram.ucTx_Buf, RS485_DATALEN - 2, &ucHByte, &ucLByte);
    RS485Fram.ucTx_Buf[RS485_DATALEN - 2] = ucHByte;
    RS485Fram.ucTx_Buf[RS485_DATALEN - 1] = ucLByte;
    
/* ���ݷ��� ------------------------------------------------------------------ */
    RS485_SendData(&RS485Fram.ucTx_Buf, RS485_DATALEN);
}


/******************************************************************************
* Name        :             Handle_ProtocolAnalysis()
* Description : �ֱ�Э���������
* Parameter   : void
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 10 / ���α�д
* Explain     : None
*******************************************************************************/
void Handle_ProtocolAnalysis(void)
{
    uint16_t usTmp;
    
/* ����ǰ������ƥ�� -------------------------------------------------------- */
    if (!RS485_MatchCorrect())
        return;
    
/* ƥ����ɣ�����Э����� ----------------------------------------------------- */
    /* ���˴ųɹ� */
    if (RS485Fram.ucRx_Buf[2] == cmd_CB_SUCCESS)
    {
        if (RS485Fram.ucRx_Buf[3] == act_Magnet_Success)
        {
            g_ulMsg |= MESSAGE_MAGNET_SUCCESS;
        }
        else if (RS485Fram.ucRx_Buf[3] == act_Demagnet_Success)
        {
            g_ulMsg |= MESSAGE_DEMAGNET_SUCCESS;
        }
    }
    /* ���˴ű��� */
    else if (RS485Fram.ucRx_Buf[2] == cmd_CB_WARNING)
    {
        if (RS485Fram.ucRx_Buf[3] == act_Magnet_Warning)
        {
            g_ulMsg |= MESSAGE_MAGNET_WAR;
        }
        else if (RS485Fram.ucRx_Buf[3] == act_Demagnet_Warning)
        {
            g_ulMsg |= MESSAGE_DEMAGNET_WAR;
        }
    }
    /* ���巵�ز��� */
    else if (RS485Fram.ucRx_Buf[2] == cmd_CB_RETV_PARAM)
    {
        usTmp = ((uint16_t)RS485Fram.ucRx_Buf[3]) << 8;
        usTmp += RS485Fram.ucRx_Buf[4];
        TM1640_Dis_Number(usTmp);
    }
    /* ���巵�ظĲγɹ� */
    else if (RS485Fram.ucRx_Buf[2] == cmd_CB_RETS_PARAM)
    {
        TM1640_DisplayOFF();
        g_usSysTestCnt = 0;
        while(g_usSysTestCnt <= 40);

        TM1640_DisplayON();
        g_usSysTestCnt = 0;
        while(g_usSysTestCnt <= 40);
        
        TM1640_DisplayOFF();
        g_usSysTestCnt = 0;
        while(g_usSysTestCnt <= 40);

        TM1640_DisplayON();
        g_usSysTestCnt = 0;
        while(g_usSysTestCnt <= 40);
    }
    /* ���������ʾ ���� */
    else if (RS485Fram.ucRx_Buf[2] == cmd_CB_RETV_MONITOR)
    {
        usTmp = ((uint16_t)RS485Fram.ucRx_Buf[3]) << 8;
        usTmp += RS485Fram.ucRx_Buf[4];
        TM1640_Dis_Number(usTmp);
    }
}
#endif


#if def_Local_ControlBoard == 1
/******************************************************************************
* Name        :             RS485_ReceiveData(void)
* Description : 485�������ݺ���
* Parameter   : void
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 - 26 / ���α�д
* Explain     : None
*******************************************************************************/
void RS485_ReceiveData(void)
{
    if (RS485Fram.ucFlg)
    {
        RS485Fram.ucFlg = 0;
        RS485Fram.ucCnt = 0;
        //@ADDЭ������ʹ���
        //@Test
        CB_ProtocolAnalysis(add_Handle);
    }
}


/******************************************************************************
* Name        :         CB_SearchPackSend(ADD_ENUM _Add)
* Description : �����ѯ������
* Parameter   : ADD_ENUM _Add           ��ַ��
* 
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 08 / ���α�д
* Explain     : ��ѯȻ���Ӧģ���Ӧ
*******************************************************************************/
void CB_SearchPackSend(ADD_ENUM _Add)
{
    uint8_t uci;
    uint8_t ucHByte,ucLByte;
    
    RS485Fram.ucTx_Buf[0] = def_FrameHead;
    RS485Fram.ucTx_Buf[1] = _Add;
    RS485Fram.ucTx_Buf[2] = 0X80;
    for (uci = 3; uci < RS485_DATALEN; uci++)
    {
        RS485Fram.ucTx_Buf[uci] = 0X55;
    }
   
    Crc16(RS485Fram.ucTx_Buf, RS485_DATALEN - 2, &ucHByte, &ucLByte);
    RS485Fram.ucTx_Buf[RS485_DATALEN - 2] = ucHByte;
    RS485Fram.ucTx_Buf[RS485_DATALEN - 1] = ucLByte;
    
    RS485_SendData(&RS485Fram.ucTx_Buf, RS485_DATALEN);
}


/******************************************************************************
* Name        :         CB_SearchPackSend(ADD_ENUM _Add)
* Description : �����ѯ������
* Parameter   : ADD_ENUM _Add           ��ַ��
* 
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 08 / ���α�д
* Explain     : ��ѯȻ���Ӧģ���Ӧ
*******************************************************************************/
void CB_PtlPackSend(ADD_ENUM _Add, CB_CMD_ENUM _Cmd, CBACTION_ENUM _Act, \
                        uint8_t _ParamNo, uint16_t _ParamValue)
{
    uint8_t uci;
    uint8_t ucHByte,ucLByte;
    
/* װ�س�ֵ ------------------------------------------------------------------ */
    RS485Fram.ucTx_Buf[0] = def_FrameHead;
    RS485Fram.ucTx_Buf[1] = _Add;
    RS485Fram.ucTx_Buf[2] = _Cmd;
    for (uci = 3; uci < RS485_DATALEN; uci++)
    {
        RS485Fram.ucTx_Buf[uci] = 0X55;
    }
    uci = 3;
    
/* ������װ�� ---------------------------------------------------------------- */
    /* ���˴ųɹ����߾������� */
    if ((_Cmd == cmd_CB_SUCCESS) || (_Cmd == cmd_CB_WARNING))
    {
        RS485Fram.ucTx_Buf[uci++] = _Act;
    }
     /* ���ز������� */
    else if (_Cmd == cmd_CB_RETV_PARAM)
    {
        RS485Fram.ucTx_Buf[uci++] = _ParamNo;
        RS485Fram.ucTx_Buf[uci++] = (uint8_t)(_ParamValue >> 8);
        RS485Fram.ucTx_Buf[uci++] = (uint8_t)(_ParamValue);
    }
   
    Crc16(RS485Fram.ucTx_Buf, RS485_DATALEN - 2, &ucHByte, &ucLByte);
    RS485Fram.ucTx_Buf[RS485_DATALEN - 2] = ucHByte;
    RS485Fram.ucTx_Buf[RS485_DATALEN - 1] = ucLByte;
    
    RS485_SendData(&RS485Fram.ucTx_Buf, RS485_DATALEN);
}


/******************************************************************************
* Name        :             CB_ProtocolAnalysis()
* Description : ����Э���������
* Parameter   : void
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 10 / ���α�д
* Explain     : None
*******************************************************************************/
void CB_ProtocolAnalysis(ADD_ENUM _Dev)
{
/* ����ǰ������ƥ�� -------------------------------------------------------- */
    if (!RS485_MatchCorrect())
        return;
    
/* ƥ����ɣ�����Э����� ----------------------------------------------------- */
/* ��������ֱ�ָ�� ---------------------------------------------------------- */
    if (_Dev == add_Handle)
    {
        /* ������ �ֱ� */
        if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_MAGNET)
        {
            //@ROON
            //@Add �����Ϣ��λ
            //�����ɣ����ֱ����ͳ�ųɹ��򱨾�����
//            Message |= MESSAGE_MAGNE;
            g_ucMagFlg = 1;
        }
        /* �����˴� �ֱ� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_DEMAGNET)
        {
            //@ROON
            //@Add �˴���Ϣ��λ
            //�˴���ɣ����ֱ����ͳ�ųɹ��򱨾�����
//            Message |= MESSAGE_DEMAG;
            g_ucMagFlg = 2;
        }
        /* ��ѯ���� �ֱ� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_SEARCH)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]ΪҪ��ѯ�Ĳ������
            //������Ҫ��ѯ�Ĳ���ֵ���ֱ�
            CB_PtlPackSend(add_Handle, cmd_CB_RETV_PARAM, 0, RS485Fram.ucRx_Buf[3], Parameter[RS485Fram.ucRx_Buf[3]].Value);
        }
        /* �޸Ĳ��� �ֱ� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_MODIFY)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]ΪҪ�޸ĵĲ������
            //@Add RS485Fram.ucRx_Buf[4]ΪҪ�޸ĵĲ���ֵ
            //�޸Ĳ����ɹ����͸Ĳγɹ�ָ����ֱ�
        }
        /* ������� �ֱ� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_MONITOR)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]ΪҪ����ͨ�����
            //���ͼ�⵽�����ݸ��ֱ�
        }
    }
/* ����������ָ�� ---------------------------------------------------------- */
    if (_Dev == add_Panel)
    {
        /* ������ ��� */
        if (RS485Fram.ucRx_Buf[2] == cmd_PANEL_MAGNET)
        {
            //@ROON
            //@Add �����Ϣ��λ
            //�����ɣ�����巢�ͳ�ųɹ��򱨾�����
        }
        /* �����˴� ��� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_PANEL_DEMAGNET)
        {
            //@ROON
            //@Add �˴���Ϣ��λ
            //�˴���ɣ�����巢�ͳ�ųɹ��򱨾�����
        }
        /* ��ѯ���� ��� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_PANEL_SEARCH)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]ΪҪ��ѯ�Ĳ������
            //������Ҫ��ѯ�Ĳ���ֵ�����
        }
        /* �޸Ĳ��� ��� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_PANEL_MODIFY)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]ΪҪ�޸ĵĲ������
            //@Add RS485Fram.ucRx_Buf[4]ΪҪ�޸ĵĲ���ֵ
            //�޸Ĳ����ɹ����͸Ĳγɹ�ָ������
        }
    }
/* �������Զ�����ָ�� ------------------------------------------------------- */
    if (_Dev == add_FarPanel)
    {
        /* ������ Զ����� */
        if (RS485Fram.ucRx_Buf[2] == cmd_FARPANEL_MAGNET)
        {
            //@ROON
            //@Add �����Ϣ��λ
            //�����ɣ���Զ����巢�ͳ�ųɹ��򱨾�����
        }
        /* �����˴� Զ����� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_FARPANEL_DEMAGNET)
        {
            //@ROON
            //@Add �˴���Ϣ��λ
            //�˴���ɣ���Զ����巢�ͳ�ųɹ��򱨾�����
        }
        /* ��ѯ���� Զ����� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_FARPANEL_SEARCH)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]ΪҪ��ѯ�Ĳ������
            //������Ҫ��ѯ�Ĳ���ֵ��Զ�����
        }
        /* �޸Ĳ��� Զ����� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_FARPANEL_MODIFY)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]ΪҪ�޸ĵĲ������
            //@Add RS485Fram.ucRx_Buf[4]ΪҪ�޸ĵĲ���ֵ
            //�޸Ĳ����ɹ����͸Ĳγɹ�ָ���Զ�����
        }
    }
/* ������մ�����ָ�� --------------------------------------------------------- */
    if (_Dev == add_Sensor)
    {
        /* ��б���� */
        if (RS485Fram.ucRx_Buf[2] == cmd_SENSOR_TILT_WAR)
        {
            //@ROON
            //@Add ��б����
        }
        /* ���ؾ��� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_SENSOR_WEIGH_WAR)
        {
            //@ROON
            //@Add ���ر���
        }
        /* �������� */
        else if (RS485Fram.ucRx_Buf[2] == cmd_SENSOR_WEIGH)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]Ϊ����ֵ
            //�洢����ֵ������ʾ
        }
    }
}
#endif


/******************************************************************************
* Name        :	  RS485_SendData(uint8_t *_pucBuf, uint8_t _ucLen)
* Description : 485�������ݺ���
* Parameter   : uint8_t *_pucBuf    �����͵����ݻ�����
*               uint8_t _ucLen      ���ݳ���
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 -04 / ���α�д
* Explain     : None
*******************************************************************************/
void RS485_SendData(uint8_t *_pucBuf, uint8_t _ucLen)
{
    uint8_t ucCnt;
    
    RS485_TX_EN();
    /* ����������� */
    for (ucCnt=0; ucCnt<=_ucLen; ucCnt++)
    {
        while (Busy1USART());
        Write1USART(*_pucBuf);
        _pucBuf++;
    }
    RS485_RX_EN();
}


/******************************************************************************
* Name        :             RS485_MatchCorrect()
* Description : ����ǰƥ�亯��
* Parameter   : void
*
* Return      : 0��ƥ��ʧ��  1��ƥ��ɹ�
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 10 / ���α�д
* Explain     : None
*******************************************************************************/
static uint8_t RS485_MatchCorrect(void)
{
    uint8_t ucHByte,ucLByte;

    /* ֡ͷƥ�� */
    if (RS485Fram.ucRx_Buf[0] != def_FrameHead)
        return 0;
    /* ��ַƥ�� */
    if (RS485Fram.ucRx_Buf[1] != def_LocalAdd)
        return 0;

    /* У��ƥ�� */
    Crc16(RS485Fram.ucRx_Buf, RS485_DATALEN - 2, &ucHByte, &ucLByte);
    if ( (ucHByte != RS485Fram.ucRx_Buf[RS485_DATALEN - 2]) 
         || (ucLByte != RS485Fram.ucRx_Buf[RS485_DATALEN - 1]) )
        return 0;
    
    return 1;
}


/******************************************************************************
* Name        :     Crc16(uint8_t *_pucBuf, uint16_t _usLen, 
*                       uint8_t *_ucHBuye, uint8_t *_ucLByte)
* Description : ����CRC16����
* Parameter   : uint8_t *_pucBuf    ��У������ݻ�����
*               uint16_t _usLen     ���ݳ���
*               uint8_t *_ucHBuye   crc16���ֽ�ָ��
*               uint8_t *_ucLByte   crc16���ֽ�ָ��
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 -25 / ���α�д
* Explain     : None
*******************************************************************************/
static void Crc16(uint8_t *_pucBuf, uint16_t _usLen, uint8_t *_ucHBuye, uint8_t *_ucLByte)
{
    uint8_t i;
    uint16_t usCrc = 0;
    
    while (_usLen > 0)
    {
        usCrc = (usCrc ^ ((uint16_t) *_pucBuf) << 8);
        for (i = 8; i > 0; i--)
        {
            if (usCrc & 0x8000)
            {
                usCrc = ((usCrc << 1) ^ def_CRC_16_POLYNOMIAL);
            }
            else
            {
                usCrc <<= 1;
            }
        }
        _pucBuf++;
        _usLen--;
    }
    *_ucHBuye = usCrc / 256;
    *_ucLByte = usCrc % 256;
}

/**************************(c) Roon**End File**********************************/

