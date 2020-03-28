/**
 * @brief
 * @file     esp8266.c
 * @author   cc
 * @version
 * @date     Sat 30 Jun 2018 11:18:12 PM PDT
 * @mail     13568859409@163.com
 * @note
 */

#include <string.h>
#include<stdio.h>
#include "../UART/uart.h"
#include "../BIGIOT/bigiot.h"
#include "esp8266.h"

// ESP8266返回数据检查正确标志，被UART使用，检查正确，将清空接收buffer.
static char mDataChekcFlag = 0xFF;
// ESP8266发送命令对应的检测结果函数
static void (*mCallBackFunction)();

// ESP8266 control mode
enum ESP8266_STATUS
{
    ESP8266_ERROR = 1,
    ESP8266_IDLE,
    ESP8266_CHECK_OK,
    ESP8266_SET_STA_MODE,
    ESP8266_CONNECT_ROUTER,
    ESP8266_DISCONNECT_ROUTER,
    ESP8266_CHECK_CONNECT_ROUTER,
    ESP8266_CHECK_IP_ADDRESS,
    ESP8266_ENABLE_AUTO_CONNECT_ROUTER,
    ESP8266_DISENABLE_AUTO_CONNECT_ROUTER,
    ESP8266_CONNECT_SERVER,
    ESP8266_DISCONNECT_SERVER,
    ESP8266_SET_TRANSMISSION_MODE,
    ESP8266_QUIT_TRANSMISSION_MODE,
    ESP8266_START_TRANSMISSION,
    ESP8266_RESET,
    ESP8266_RESET_TO_FACTORY
};

// ESP8266 control struct
typedef struct
{
    enum ESP8266_STATUS CurrentStatus;
    enum ESP8266_STATUS NextStatus;
    char AutoConnectWiFi;                   // Auto connect to WiFi

}ESP8266_Control_St;

// 定义ESP8266模块控制结构体
ESP8266_Control_St mEsp8266ControlSt;

/**
 *@brief  Esp8266状态改变处理函数
 *@param  aSt:控制结构体
 *@return None
 */
static void Esp8266StatusChange(void);

/**
 *@brief  Esp8266返回数据中OK检查
 *@return None
 */
static void Esp8266ReturnDataOKCheck(char *recv_data)
{
    if(NULL != strstr(recv_data, "OK"))
    {
        mDataChekcFlag = 0;
        if(NULL != mCallBackFunction)
        {
            (*mCallBackFunction)();
            //mCallBackFunction = NULL;
        }
    }
}

/**
 *@brief  Esp8266数据检查
 *@return 成功：0  失败：-1
 */
char GetEsp8266DataCheckFlag(void)
{
    return mDataChekcFlag;
}

/**
 *@brief  Esp8266数据检查设置
 *@return None
 */
void SetEsp8266DataCheckFlag(void)
{
    mDataChekcFlag = 0xFF;
}

/**
 *@brief Esp8266模块初始化
 *@param None
 */
void Esp8266Init(void)
{
    mCallBackFunction = NULL;
    memset(&mEsp8266ControlSt, 0, sizeof(ESP8266_Control_St));
    mEsp8266ControlSt.AutoConnectWiFi = 0;
    mEsp8266ControlSt.CurrentStatus = ESP8266_ERROR;
    mEsp8266ControlSt.NextStatus = ESP8266_CHECK_OK;
    Esp8266StatusChange();
}

/**
 *@brief Esp8266模块检测结果
 *@param None
 */
static void Esp8266CheckCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266CheckCallbackFunc OK\n");
#endif
    mEsp8266ControlSt.CurrentStatus = ESP8266_CHECK_OK;
    mEsp8266ControlSt.NextStatus = ESP8266_SET_STA_MODE;
    Esp8266StatusChange();
}

/**
 *@brief Esp8266模块检测
 *@param None
 */
void Esp8266Check(void)
{
    UART_SendString(USING_UART_PORT_2, "AT\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266CheckCallbackFunc;
}

/**
 *@brief  Esp8266模块重启结果
 *@return None
 */
static void Esp8266ReseatCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266ReseatCallbackFunc OK\n");
#endif
}

/**
 *@brief  Esp8266模块硬件重启
 *@return None
 */
void Esp8266HartReseat(void)
{
}

/**
 *@brief  Esp8266模块重启
 *@return None
 */
void Esp8266Reseat(void)
{
    UART_SendString(USING_UART_PORT_2, "AT+RST\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266ReseatCallbackFunc;
}

/**
 *@brief  Esp8266恢复出厂设置结果
 *@return None
 */
 static void Esp8266ResetFactoryDataCallbackFunc(void)
 {
 #if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266ResetFactoryDataCallbackFunc OK\n");
#endif
 }

/**
 *@brief  Esp8266恢复出厂设置
 *@return None
 */
void Esp8266ResetFactoryData(void)
{
    UART_SendString(USING_UART_PORT_2, "AT+RESTORE\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266ResetFactoryDataCallbackFunc;
}

/**
 *@brief  Esp8266模块应用模式结果
 *@param  None
 *@return None
 */
static void Esp8266SetSTAModeCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266SetSTAModeCallbackFunc OK\n");
#endif
    mEsp8266ControlSt.CurrentStatus = ESP8266_SET_STA_MODE;
    mEsp8266ControlSt.NextStatus = ESP8266_CONNECT_ROUTER;
    Esp8266StatusChange();
}

/**
 *@brief  Esp8266模块STA应用模式
 *@param  None
 *@return None
 */
void Esp8266SetSTAMode(void)
{
    UART_SendString(USING_UART_PORT_2, "AT+CWMODE=1\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266SetSTAModeCallbackFunc;
}

/**
 *@brief  Esp8266模块设置路由器结果
 *@param  None
 *@return None
 */
static void Esp8266SetRouterCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266SetRouterCallbackFunc OK\n");
#endif
    mEsp8266ControlSt.CurrentStatus = ESP8266_CONNECT_ROUTER;
    mEsp8266ControlSt.NextStatus = ESP8266_CHECK_CONNECT_ROUTER;
    Esp8266StatusChange();
}

/**
 *@brief  Esp8266模块设置路由器
 *@param  ssid:路由器名 password:密码
 *@return None
 */
void Esp8266SetRouter(const char *ssid,const char *password)
{
    char theSendPtr[100] = {0};
    sprintf(theSendPtr,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,password);
    UART_SendString(USING_UART_PORT_2, theSendPtr, Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266SetRouterCallbackFunc;
}

/**
 *@brief  Esp8266查看连接路由器结果
 *@return None
 */
static void Esp8266CheckConnectRouterCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266CheckConnectRouterCallbackFunc OK\n");
#endif
// Balder_test -->
    /*
    AT+CWJAP?
    +CWJAP:"TP-LINK_028A","ec:26:ca:06:02:8a",1,-53,0

    OK
    */
// <-- Balder_test
    mEsp8266ControlSt.CurrentStatus = ESP8266_CHECK_CONNECT_ROUTER;
    mEsp8266ControlSt.NextStatus = ESP8266_CHECK_IP_ADDRESS;
    Esp8266StatusChange();
}

/**
 *@brief  Esp8266查看连接路由器
 *@return None
 */
void Esp8266CheckConnectRouter(void)
{
    UART_SendString(USING_UART_PORT_2, "AT+CWJAP?\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266CheckConnectRouterCallbackFunc;
}

/**
 *@brief  Esp8266模块IP获取结果
 *@param  None
 *@return None
 */
static void Esp8266GetLocalIPAddrCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266GetLocalIPAddrCallbackFunc OK\n");
#endif
// Balder_test -->
    /*
    AT+CIFSR
    +CIFSR:STAIP,"192.168.1.114"
    +CIFSR:STAMAC,"bc:dd:c2:ba:89:6a"

    OK
    */
// <-- Balder_test
    mEsp8266ControlSt.CurrentStatus = ESP8266_CHECK_IP_ADDRESS;
    //mEsp8266ControlSt->NextStatus = ESP8266_ENABLE_AUTO_CONNECT_ROUTER;         // Need modify
    mEsp8266ControlSt.NextStatus = ESP8266_CONNECT_SERVER;
    Esp8266StatusChange();
}

/**
 *@brief  Esp8266模块IP获取
 *@param  None
 *@return None
 */
void Esp8266GetLocalIPAddr(void)
{
    UART_SendString(USING_UART_PORT_2, "AT+CIFSR\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266GetLocalIPAddrCallbackFunc;
}

/**
 *@brief  Esp8266模块连接到服务器的结果
 *@param  None
 *@return None
 */
static void Esp8266ConnectServerCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266ConnectServerCallbackFunc OK\n");
#endif
    mEsp8266ControlSt.CurrentStatus = ESP8266_CONNECT_SERVER;
    mEsp8266ControlSt.NextStatus = ESP8266_SET_TRANSMISSION_MODE;
    Esp8266StatusChange();
}

/**
 *@brief  Esp8266模块连接到服务器
 *@param  type:通信协议类型 ip:服务器ip地址 port服务器端口
 *@return None
 */
void Esp8266ConnectServer(const char *type,const char *ip,const unsigned int port)
{
    char theSendPtr[100] = {0};
    sprintf(theSendPtr,"AT+CIPSTART=\"%s\",\"%s\",%d\r\n",type,ip,port);
    UART_SendString(USING_UART_PORT_2, theSendPtr, Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266ConnectServerCallbackFunc;
}

/**
 *@brief  Esp8266模块设置开启透传模式的结果
 *@param  None
 *@return None
 */
static void Esp8266SetTransModeCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266SetTransModeCallbackFunc OK\n");
#endif
    mEsp8266ControlSt.CurrentStatus = ESP8266_SET_TRANSMISSION_MODE;
    mEsp8266ControlSt.NextStatus = ESP8266_START_TRANSMISSION;
    Esp8266StatusChange();

}

/**
 *@brief  Esp8266模块设置开启透传模式
 *@param  None
 *@return None
 */
void Esp8266SetTransMode(void)
{
    UART_SendString(USING_UART_PORT_2, "AT+CIPMODE=1\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266SetTransModeCallbackFunc;
}

/**
 *@brief  Esp8266模块开始透传的结果
 *@param  None
 *@return None
 */
static void Esp8266StartTransmissionCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266StartTransmissionCallbackFunc OK\n");
#endif
    mEsp8266ControlSt.CurrentStatus = ESP8266_START_TRANSMISSION;
    mEsp8266ControlSt.NextStatus = ESP8266_IDLE;                       // Entery the send data mode
    Esp8266StatusChange();
}

/**
 *@brief  Esp8266模块开始透传
 *@param  None
 *@return None
 */
void Esp8266StartTransmission(void)
{
    UART_SendString(USING_UART_PORT_2, "AT+CIPSEND\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266StartTransmissionCallbackFunc;
}

/**
 *@brief  Esp8266模块发送数据
 *@param  data:发送的数据字符串,此时不需要添加回车
 *@param  aCallback:如果需要响应，则该函数为响应数据函数
 *@return None
 */
void Esp8266SendData(const char *data, void *aCallback)
{
    if(ESP8266_IDLE == mEsp8266ControlSt.CurrentStatus)
    {
        UART_SendString(USING_UART_PORT_2, data, aCallback);
    }
}

/**
 *@brief  Esp8266退出透传模式
 *@param  None
 *@return None
 */
void Esp8266QuitTransmission(void)
{
    UART_SendString(USING_UART_PORT_2, "+++", NULL);
}

/**
 *@brief  Esp8266退出与路由器的AP连接的结果
 *@return None
 */
static void Esp8266QuitRouterAPConnectCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266QuitRouterAPConnectCallbackFunc OK\n");
#endif
}

/**
 *@brief  Esp8266退出与路由器的AP连接
 *@return None
 */
void Esp8266QuitRouterAPConnect(void)
{
    UART_SendString(USING_UART_PORT_2, "AT+CWQAP\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266QuitRouterAPConnectCallbackFunc;
}

/**
 *@brief  Esp8266设置STA开机自动连接的结果
 *@param  None
 *@return None
 */
static void Esp8266SetSTAAutoConnectCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266SetSTAAutoConnectCallbackFunc OK\n");
#endif
}

/**
 *@brief  Esp8266设置STA开机自动连接
 *@param  enable:使能控制
 *@return None
 */
void Esp8266SetSTAAutoConnect(unsigned char enable)
{
    if(1 == enable)
    {
        UART_SendString(USING_UART_PORT_2, "AT+CWAUTOCONN=1\r\n", Esp8266ReturnDataOKCheck);
    }
    else
    {
        UART_SendString(USING_UART_PORT_2, "AT+CWAUTOCONN=0\r\n", Esp8266ReturnDataOKCheck);
    }
    mCallBackFunction = Esp8266SetSTAAutoConnectCallbackFunc;
}

/**
 *@brief  Esp8266断开TCP或者UDP连接的结果
 *@param  None
 *@return None
 */
static void Esp8266DisableConnectCallbackFunc(void)
{
#if defined BSP_ENABLE_ESP8266_DEBUG
    rt_kprintf("Esp8266DisableConnectCallbackFunc OK\n");
#endif
}

/**
 *@brief  Esp8266断开TCP或者UDP连接
 *@param  None
 *@return None
 */
void Esp8266DisableConnect(void)
{
    UART_SendString(USING_UART_PORT_2, "AT+CIPCLOSE\r\n", Esp8266ReturnDataOKCheck);
    mCallBackFunction = Esp8266DisableConnectCallbackFunc;
}

/**
 *@brief  Esp8266状态改变处理函数
 *@param  None
 *@return None
 */
static void Esp8266StatusChange(void)
{
    switch(mEsp8266ControlSt.NextStatus)
    {
    case ESP8266_CHECK_OK:
        Esp8266Check();
        break;
    case ESP8266_SET_STA_MODE:
        Esp8266SetSTAMode();
        break;
    case ESP8266_CONNECT_ROUTER:
        Esp8266SetRouter(ESP8266_SSID, ESP8266_PASSWORLD);      // Current just for test
        break;
    case ESP8266_DISCONNECT_ROUTER:
        Esp8266QuitRouterAPConnect();
        break;
    case ESP8266_CHECK_CONNECT_ROUTER:
        Esp8266CheckConnectRouter();
        break;
    case ESP8266_CHECK_IP_ADDRESS:
        Esp8266GetLocalIPAddr();
        break;
    case ESP8266_ENABLE_AUTO_CONNECT_ROUTER:
        Esp8266SetSTAAutoConnect(1);
        break;
    case ESP8266_DISENABLE_AUTO_CONNECT_ROUTER:
        Esp8266SetSTAAutoConnect(0);
        break;
    case ESP8266_CONNECT_SERVER:
        Esp8266ConnectServer("TCP",ESP8266_CONNECT_TCP_SERVER, ESP8266_CONNECT_TCP_PORT);      // Current just for test
        break;
    case ESP8266_DISCONNECT_SERVER:
        Esp8266DisableConnect();
        break;
    case ESP8266_SET_TRANSMISSION_MODE:
        Esp8266SetTransMode();
        break;
    case ESP8266_QUIT_TRANSMISSION_MODE:
        Esp8266QuitTransmission();
        break;
    case ESP8266_START_TRANSMISSION:
        Esp8266StartTransmission();
        break;
    case ESP8266_RESET:
        Esp8266Reseat();
        break;
    case ESP8266_RESET_TO_FACTORY:
        Esp8266ResetFactoryData();
        break;
    case ESP8266_IDLE:
        // ESP8266 module is ready to send data
        mEsp8266ControlSt.CurrentStatus = ESP8266_IDLE;
        BigiotLogin((const char *)BIGIOT_SMART_HOUSE_ID,(const char *)BIGIOT_SMART_HOUSE_APIKEY);
        break;
    case ESP8266_ERROR:
    default:
        // ESP8266 module is not ready
        break;
    }
    rt_thread_mdelay(1000);
}

/**
 *@brief Esp8266设置连接到WiFi参数
 *@param ssid: WiFi名  password: WiFi密码  aCallback:设置参数成功与否的回调函数
 *@return None
 */
void Esp8266SetRouterParameter(const char *ssid,const char *password, void *aCallback)
{

}

/**
 *@brief  Esp8266模块连接到服务器参数
 *@param  type:通信协议类型 ip:服务器ip地址 port服务器端口 aCallback:设置参数成功与否的回调函数
 *@return None
 */
void Esp8266ConnectServerParameter(const char *type,const char *ip,const unsigned int port, void *aCallback)
{

}


