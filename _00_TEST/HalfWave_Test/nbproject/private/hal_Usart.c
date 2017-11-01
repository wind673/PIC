/**************************(c) Roon**Start File********************************/
/*=============================================================================
* File   Name : hal_Usart.c
* Description : 底层串口驱动文件
* Date        : 2015 - 10 - 08
* By          : 张 飞
* E-mail      : roonmobi@126.com
* Platform    : MPLAB X IDE v3.10 (pic18f67k22)
* Explain     :
*=============================================================================*/

/* 头文件包含 -----------------------------------------------------------------*/
#include "hal_Usart.h"

/* 私有宏定义 -----------------------------------------------------------------*/
/* 本机地址选择 1为选中 0不选中 ------------------------------------------------*/
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

/* CRC16 多项式 */
#define def_CRC_16_POLYNOMIAL           0X1021  //0X8005

/* 帧头数据 */
#define def_FrameHead                   0XAA

/* 私有变量定义 ---------------------------------------------------------------*/
extern volatile uint16_t g_usSysTestCnt;
extern volatile uint32_t Message;
extern __Parameter Parameter[PARAM_NUM+1];

volatile uint8_t g_ucMagFlg = 0;

/* 静态函数声明 ---------------------------------------------------------------*/
static uint8_t RS485_MatchCorrect(void);
//static void RS485_ProtocolAnalysis(void);
static void Crc16(uint8_t *_pucBuf, uint16_t _usLen, uint8_t *_ucHBuye, uint8_t *_ucLByte);

/* 函数编写 -------------------------------------------------------------------*/
/******************************************************************************
* Name        :		       RS485_halInit()
* Description : 串口物理层初始化函数
* Parameter   : void
*
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 -04 / 初次编写
* Explain     : None
*******************************************************************************/
void RS485_halInit(void)
{
    /* 串口配置 9600波特率 */
    Open1USART( USART_TX_INT_OFF &
                USART_RX_INT_ON &
                USART_ASYNCH_MODE &
                USART_EIGHT_BIT &
                USART_CONT_RX &
                USART_BRGH_LOW,
                51);
    
    /* 485模式控制 GPIO 初始化 */
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC7 = 1;
 //    ANCON2 &= 0XF9;
    
    /* 开中断 */
    _rn_EN_ALLINT();
    _rn_EN_PERINT();
    
    /* RS485处于接收模式 */
    RS485_RX_EN();
}


#if def_Local_Handle == 1
/******************************************************************************
* Name        :             RS485_ReceiveData(void)
* Description : 485接收数据函数
* Parameter   : void
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 - 26 / 初次编写
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
* Description : 手柄协议包发送
* Parameter   : ADD_ENUM _Add           地址码
*               HANDLE_CMD_ENUM _Cmd    功能码
*               uint8_t _ParamNo        参数序号
*               uint16_t _ParamValue    参数值
*               uint8_t _Ch             通道
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 08 / 初次编写
* Explain     : 具体见协议参考文件
*******************************************************************************/
void Handle_PtlPackSend(ADD_ENUM _Add, HANDLE_CMD_ENUM _Cmd, uint8_t _ParamNo,\
                            uint16_t _ParamValue, uint8_t _Ch)
{
    uint8_t uci;
    uint8_t ucHByte,ucLByte;
    
/* 装载初值 ------------------------------------------------------------------ */
    RS485Fram.ucTx_Buf[0] = def_FrameHead;
    RS485Fram.ucTx_Buf[1] = _Add;
    RS485Fram.ucTx_Buf[2] = _Cmd;
    for (uci = 3; uci < RS485_DATALEN; uci++)
    {
        RS485Fram.ucTx_Buf[uci] = 0X55;
    }
    uci = 3;
    
/* 功能码装载 ---------------------------------------------------------------- */
    /* 手柄查询命令 */
    if (_Cmd == cmd_HANDLE_SEARCH)
    {
        RS485Fram.ucTx_Buf[uci++] = _ParamNo;
    }
    /* 手柄修改命令 */
    else if (_Cmd == cmd_HANDLE_MODIFY)
    {
        RS485Fram.ucTx_Buf[uci++] = _ParamNo;
        RS485Fram.ucTx_Buf[uci++] = (uint8_t)(_ParamValue >> 8);
        RS485Fram.ucTx_Buf[uci++] = (uint8_t)(_ParamValue);
    }
    /* 手柄监测命令 */
    else if (_Cmd == cmd_HANDLE_MONITOR)
    {
        RS485Fram.ucTx_Buf[uci++] = _Ch;
    }
    
/* 校验码装载 ---------------------------------------------------------------- */
    Crc16(RS485Fram.ucTx_Buf, RS485_DATALEN - 2, &ucHByte, &ucLByte);
    RS485Fram.ucTx_Buf[RS485_DATALEN - 2] = ucHByte;
    RS485Fram.ucTx_Buf[RS485_DATALEN - 1] = ucLByte;
    
/* 数据发送 ------------------------------------------------------------------ */
    RS485_SendData(&RS485Fram.ucTx_Buf, RS485_DATALEN);
}


/******************************************************************************
* Name        :             Handle_ProtocolAnalysis()
* Description : 手柄协议解析函数
* Parameter   : void
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 10 / 初次编写
* Explain     : None
*******************************************************************************/
void Handle_ProtocolAnalysis(void)
{
    uint16_t usTmp;
    
/* 解析前，纠错及匹配 -------------------------------------------------------- */
    if (!RS485_MatchCorrect())
        return;
    
/* 匹配完成，数据协议解析 ----------------------------------------------------- */
    /* 充退磁成功 */
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
    /* 充退磁报警 */
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
    /* 主板返回参数 */
    else if (RS485Fram.ucRx_Buf[2] == cmd_CB_RETV_PARAM)
    {
        usTmp = ((uint16_t)RS485Fram.ucRx_Buf[3]) << 8;
        usTmp += RS485Fram.ucRx_Buf[4];
        TM1640_Dis_Number(usTmp);
    }
    /* 主板返回改参成功 */
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
    /* 监测数据显示 电流 */
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
* Description : 485接收数据函数
* Parameter   : void
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 - 26 / 初次编写
* Explain     : None
*******************************************************************************/
void RS485_ReceiveData(void)
{
    if (RS485Fram.ucFlg)
    {
        RS485Fram.ucFlg = 0;
        RS485Fram.ucCnt = 0;
        //@ADD协议解析和处理
        //@Test
        CB_ProtocolAnalysis(add_Handle);
    }
}


/******************************************************************************
* Name        :         CB_SearchPackSend(ADD_ENUM _Add)
* Description : 主板查询包发送
* Parameter   : ADD_ENUM _Add           地址码
* 
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 08 / 初次编写
* Explain     : 查询然后对应模块回应
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
* Description : 主板查询包发送
* Parameter   : ADD_ENUM _Add           地址码
* 
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 08 / 初次编写
* Explain     : 查询然后对应模块回应
*******************************************************************************/
void CB_PtlPackSend(ADD_ENUM _Add, CB_CMD_ENUM _Cmd, CBACTION_ENUM _Act, \
                        uint8_t _ParamNo, uint16_t _ParamValue)
{
    uint8_t uci;
    uint8_t ucHByte,ucLByte;
    
/* 装载初值 ------------------------------------------------------------------ */
    RS485Fram.ucTx_Buf[0] = def_FrameHead;
    RS485Fram.ucTx_Buf[1] = _Add;
    RS485Fram.ucTx_Buf[2] = _Cmd;
    for (uci = 3; uci < RS485_DATALEN; uci++)
    {
        RS485Fram.ucTx_Buf[uci] = 0X55;
    }
    uci = 3;
    
/* 功能码装载 ---------------------------------------------------------------- */
    /* 充退磁成功或者警告命令 */
    if ((_Cmd == cmd_CB_SUCCESS) || (_Cmd == cmd_CB_WARNING))
    {
        RS485Fram.ucTx_Buf[uci++] = _Act;
    }
     /* 返回参数命令 */
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
* Description : 主板协议解析函数
* Parameter   : void
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 10 / 初次编写
* Explain     : None
*******************************************************************************/
void CB_ProtocolAnalysis(ADD_ENUM _Dev)
{
/* 解析前，纠错及匹配 -------------------------------------------------------- */
    if (!RS485_MatchCorrect())
        return;
    
/* 匹配完成，数据协议解析 ----------------------------------------------------- */
/* 主板接收手柄指令 ---------------------------------------------------------- */
    if (_Dev == add_Handle)
    {
        /* 主板充磁 手柄 */
        if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_MAGNET)
        {
            //@ROON
            //@Add 充磁消息置位
            //充磁完成，向手柄发送充磁成功或报警命令
//            Message |= MESSAGE_MAGNE;
            g_ucMagFlg = 1;
        }
        /* 主板退磁 手柄 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_DEMAGNET)
        {
            //@ROON
            //@Add 退磁消息置位
            //退磁完成，向手柄发送充磁成功或报警命令
//            Message |= MESSAGE_DEMAG;
            g_ucMagFlg = 2;
        }
        /* 查询参数 手柄 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_SEARCH)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]为要查询的参数序号
            //发送需要查询的参数值给手柄
            CB_PtlPackSend(add_Handle, cmd_CB_RETV_PARAM, 0, RS485Fram.ucRx_Buf[3], Parameter[RS485Fram.ucRx_Buf[3]].Value);
        }
        /* 修改参数 手柄 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_MODIFY)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]为要修改的参数序号
            //@Add RS485Fram.ucRx_Buf[4]为要修改的参数值
            //修改参数成功后发送改参成功指令给手柄
        }
        /* 监测数据 手柄 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_HANDLE_MONITOR)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]为要监测的通道序号
            //发送监测到的数据给手柄
        }
    }
/* 主板接收面板指令 ---------------------------------------------------------- */
    if (_Dev == add_Panel)
    {
        /* 主板充磁 面板 */
        if (RS485Fram.ucRx_Buf[2] == cmd_PANEL_MAGNET)
        {
            //@ROON
            //@Add 充磁消息置位
            //充磁完成，向面板发送充磁成功或报警命令
        }
        /* 主板退磁 面板 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_PANEL_DEMAGNET)
        {
            //@ROON
            //@Add 退磁消息置位
            //退磁完成，向面板发送充磁成功或报警命令
        }
        /* 查询参数 面板 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_PANEL_SEARCH)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]为要查询的参数序号
            //发送需要查询的参数值给面板
        }
        /* 修改参数 面板 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_PANEL_MODIFY)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]为要修改的参数序号
            //@Add RS485Fram.ucRx_Buf[4]为要修改的参数值
            //修改参数成功后发送改参成功指令给面板
        }
    }
/* 主板接收远程面板指令 ------------------------------------------------------- */
    if (_Dev == add_FarPanel)
    {
        /* 主板充磁 远程面板 */
        if (RS485Fram.ucRx_Buf[2] == cmd_FARPANEL_MAGNET)
        {
            //@ROON
            //@Add 充磁消息置位
            //充磁完成，向远程面板发送充磁成功或报警命令
        }
        /* 主板退磁 远程面板 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_FARPANEL_DEMAGNET)
        {
            //@ROON
            //@Add 退磁消息置位
            //退磁完成，向远程面板发送充磁成功或报警命令
        }
        /* 查询参数 远程面板 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_FARPANEL_SEARCH)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]为要查询的参数序号
            //发送需要查询的参数值给远程面板
        }
        /* 修改参数 远程面板 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_FARPANEL_MODIFY)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]为要修改的参数序号
            //@Add RS485Fram.ucRx_Buf[4]为要修改的参数值
            //修改参数成功后发送改参成功指令给远程面板
        }
    }
/* 主板接收传感器指令 --------------------------------------------------------- */
    if (_Dev == add_Sensor)
    {
        /* 倾斜警告 */
        if (RS485Fram.ucRx_Buf[2] == cmd_SENSOR_TILT_WAR)
        {
            //@ROON
            //@Add 倾斜报警
        }
        /* 称重警告 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_SENSOR_WEIGH_WAR)
        {
            //@ROON
            //@Add 称重报警
        }
        /* 称重重量 */
        else if (RS485Fram.ucRx_Buf[2] == cmd_SENSOR_WEIGH)
        {
            //@ROON
            //@Add RS485Fram.ucRx_Buf[3]为称重值
            //存储称重值或者显示
        }
    }
}
#endif


/******************************************************************************
* Name        :	  RS485_SendData(uint8_t *_pucBuf, uint8_t _ucLen)
* Description : 485发送数据函数
* Parameter   : uint8_t *_pucBuf    待发送的数据缓冲区
*               uint8_t _ucLen      数据长度
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 -04 / 初次编写
* Explain     : None
*******************************************************************************/
void RS485_SendData(uint8_t *_pucBuf, uint8_t _ucLen)
{
    uint8_t ucCnt;
    
    RS485_TX_EN();
    /* 逐个发送数据 */
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
* Description : 解析前匹配函数
* Parameter   : void
*
* Return      : 0：匹配失败  1：匹配成功
* Programer   : Roon_Zhang
* Data	      : 2015 - 10 - 10 / 初次编写
* Explain     : None
*******************************************************************************/
static uint8_t RS485_MatchCorrect(void)
{
    uint8_t ucHByte,ucLByte;

    /* 帧头匹配 */
    if (RS485Fram.ucRx_Buf[0] != def_FrameHead)
        return 0;
    /* 地址匹配 */
    if (RS485Fram.ucRx_Buf[1] != def_LocalAdd)
        return 0;

    /* 校验匹配 */
    Crc16(RS485Fram.ucRx_Buf, RS485_DATALEN - 2, &ucHByte, &ucLByte);
    if ( (ucHByte != RS485Fram.ucRx_Buf[RS485_DATALEN - 2]) 
         || (ucLByte != RS485Fram.ucRx_Buf[RS485_DATALEN - 1]) )
        return 0;
    
    return 1;
}


/******************************************************************************
* Name        :     Crc16(uint8_t *_pucBuf, uint16_t _usLen, 
*                       uint8_t *_ucHBuye, uint8_t *_ucLByte)
* Description : 计算CRC16函数
* Parameter   : uint8_t *_pucBuf    待校验的数据缓冲区
*               uint16_t _usLen     数据长度
*               uint8_t *_ucHBuye   crc16高字节指针
*               uint8_t *_ucLByte   crc16低字节指针
*
* Return      : void
* Programer   : Roon_Zhang
* Data	      : 2015 - 09 -25 / 初次编写
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

