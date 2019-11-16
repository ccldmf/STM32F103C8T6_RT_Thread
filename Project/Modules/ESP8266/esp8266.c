/**
  ******************************************************************************
  * @file    Modules/ESP/esp8266.c
  * @author  CC
  * @version V1.0.0
  * @date    03-11-2019
  * @brief   STM32F103C8T6 development board for use ESP8266 module.
  *          This file provides control the ESP8266 on the STM32F103C8T6 development
  *          board.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "esp8266.h"
#include "usart.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>

#if !defined (USART1_ESP8266) && !defined (USART2_ESP8266) && !defined (USART3_ESP8266)
    /* #define USART1_ESP8266 */     /*!< USART1_PRINTF: Use USART1 for ESP8266 module communication */
    /* #define USART2_ESP8266 */     /*!< USART2_PRINTF: Use USART2 for ESP8266 module communication */
    /* #define USART3_ESP8266 */     /*!< USART3_PRINTF: Use USART3 for ESP8266 module communication */
#endif

#if !defined (USART1_ESP8266) && !defined (USART2_ESP8266) && !defined (USART3_ESP8266)
 #error "Please select a USART for ESP8266 module communication(in esp8266.c file)"
#endif

#if 0
const uint8_t *WIFI_ROUT_NAME      = "TP-LINK_028A";
const uint8_t *WIFI_ROUT_PASS      =  "ccldmf1994";
const uint8_t *CONNECT_SERVER_TYPE = "TCP";
const uint8_t *CONNECT_SERVER_IP   = "192.168.1.100";
const uint32_t CONNECT_SERVER_PORT = 8080;


// Define global parameters
static u8  mRecvDataBuf[RECV_BUF_SIZE] = {0};
static uint16_t mRecvDataCount = 0;
static uint16_t mRecvPreDataCount = 0;

void USART1_IRQHandler(void)
{
    u8 res;
    if(USART_GetITStatus(USART1,USART_IT_RXNE))
    {
        if ( mRecvDataCount >= RECV_BUF_SIZE )
            mRecvDataCount = 0;
        mRecvDataBuf[mRecvDataCount++] = USART1->DR;
        USART_ClearFlag(USART1, USART_FLAG_RXNE);
    }
}

/**
  * @brief  Clear all recv data
  * @param  None
  * @retval None
  */
static void Esp8266RecvClear(void)
{
    uint16_t i;
    //USART_ClearFlag(USART1,USART_FLAG_RXNE);
    mRecvDataCount = 0;
    #if 1
    for( i = 0 ; i < RECV_BUF_SIZE ; i++)
    {
    mRecvDataBuf[i] = 0;
    }
    #endif
}

/**
  * @brief  Esp8266 Init
  * @param  None
  * @retval None
  */
 uint8_t Esp8266Init(void)
{
    printf("************************************\n");
    printf("*          ESP8266 Iinit           *\n");
    printf("************************************\n");
    printf("**Step 1:AT\n");
    while(Esp8266SendCmd("AT", "OK"))
        Delay_ms(500);
    printf("**Step 2:Esp8266SetMode\n");
    while(Esp8266SetMode(1))
        Delay_ms(500);
    printf("**Step 3:Esp8266SetDHCP\n");
    while(Esp8266SetDHCP(1, 1))
        Delay_ms(500);
    printf("**Step 4:Esp8266SetRouter\n");
    while(Esp8266SetRouter(WIFI_ROUT_NAME, WIFI_ROUT_PASS))
        Delay_ms(500);
    printf("**Step 5:Esp8266ConnectServer\n");
    while(Esp8266ConnectServer(CONNECT_SERVER_TYPE, CONNECT_SERVER_IP,CONNECT_SERVER_PORT))
        Delay_ms(500);
    printf("*          ESP8266 Init OK         *\n");
    return 0;
}

/**
  * @brief  Esp8266 Close
  * @param  None
  * @retval None
  */
uint8_t Esp8266Close(void)
{
    mRecvDataCount = 0;
    return 0;
}

static uint8_t Esp8266WaitRecv(void)
{
    if( mRecvDataCount == 0 )
        return 1;
    if( mRecvDataCount == mRecvPreDataCount )
    {
        mRecvDataCount = 0;
        return 0;
    }
    mRecvPreDataCount = mRecvDataCount;
    return 1;
}

/**
  * @brief  Esp8266 Send Command
  * @param  cmd:Command
  *         ack:Expected return data.
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SendCmd(const uint8_t *cmd , const uint8_t *ack )
{
    uint8_t theRet;
    USART_TypeDef *ESP8266_USARTx;
    u8 theTimeOut = 0;

#ifdef USART1_ESP8266
    ESP8266_USARTx = USART1;
#elif USART2_ESP8266
    ESP8266_USARTx = USART2;
#else
    ESP8266_USARTx = USART3;
#endif

    Esp8266RecvClear();
    USART_SendString(ESP8266_USARTx,cmd);

    while( theTimeOut++ < WAIT_RECV_DATA_TIME_COUNT )
    {
        if( Esp8266WaitRecv() == 0 )
        {
            if ( NULL != strstr( (const char*)mRecvDataBuf , (const char*)ack))
            {
                printf("RecvData:%s\n",mRecvDataBuf);
                printf("mRecvDataCount:%d\n",mRecvDataCount);
                Esp8266RecvClear();
                return 0;
            }
        }
        Delay_ms(10);
    }
    return 1;
}

/**
  * @brief  Esp8266 restart
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266Reseat(void)
{
    uint8_t ret = 0xFF;
    ret = Esp8266SendCmd("AT+RST","OK");
    return ret;
}

/**
  * @brief  Esp8266 echo function set
  * @param  flag: 1 or 0
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetReturnDisplay(uint8_t flag)
{
    uint8_t ret = 0xFF;
    if(0 == flag)
    {
        ret = Esp8266SendCmd("ATE0","OK");
    }
    else if(1 == flag)
    {
        ret = Esp8266SendCmd("ATE1","OK");
    }
    return ret;
}

/**
  * @brief  Esp8266 reset factory data
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266ResetFactoryData(void)
{
    uint8_t ret = 0xFF;
    ret = Esp8266SendCmd("AT+RESTORE","OK");
    return ret;
}

 /**
  * @brief  Esp8266 set mode
  * @param  mode: 1/2/3
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetMode(enum WIFIMODE mode)
{
    uint8_t ret = 0xFF;
    const uint8_t *theCmd;
    if ( WIFI_STATION == mode )
    {
        theCmd = COMMAND("AT+CWMODE=1");
    }
    else if ( WIFI_AP == mode )
    {
        theCmd = COMMAND("AT+CWMODE=2");
    }
    else if ( WIFI_AP_STATION == mode )
    {
        theCmd = COMMAND("AT+CWMODE=3");
    }
    ret = Esp8266SendCmd(theCmd,"OK");

    return ret;
}

 /**
  * @brief  Esp8266 set DHCP
  * @param
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetDHCP(u8 mode,u8 enable)
{
    uint8_t ret = 0xFF;
    const uint8_t *theCmd;
    theCmd = COMMAND("AT+CWDHCP=1,1");
    ret = Esp8266SendCmd(theCmd,"OK");

    return ret;
}

/**
  * @brief  Esp8266 set connect router
  * @param  ssid: Router name
  *         password: Router password
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetRouter(const uint8_t *ssid , const uint8_t *password)
{
    uint8_t ret = 0xFF;
    uint8_t theSendPtr[60] = {0};
    sprintf(theSendPtr,"AT+CWJAP=\"%s\",\"%s\"",ssid,password);
    ret = Esp8266SendCmd(theSendPtr,"WIFI CONNECTED");
    return ret;
}

/**
  * @brief  Esp8266 disconnect router
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266QuitRouterAPConnect(void)
{
    uint8_t ret = 0xFF;
    ret = Esp8266SendCmd("AT+CWQAP","OK");
    return ret;
}

/**
  * @brief  Esp8266 Set STA boot auto connection
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetSTAAutoConnect()
{
    uint8_t ret = 0xFF;
    ret = Esp8266SendCmd("AT+CWAUTOCONN=1" , "OK");
    return ret;
}
#endif

/**
  * @brief  Esp8266 send data
  * @param  data:send data
  *         ack:response data
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SendData(const uint8_t *data , const uint8_t *ack)
{
    uint8_t ret = 0xFF;
    USART_TypeDef *ESP8266_USARTx;

#ifdef USART1_ESP8266
    ESP8266_USARTx = USART1;
#elif USART2_ESP8266
    ESP8266_USARTx = USART2;
#else
    ESP8266_USARTx = USART3;
#endif

    USART_SendString(ESP8266_USARTx , data);
    // if ack is not NULL,it means need check the return data.
    if(ack != NULL)
    {
    #if 0
        uint8_t *theRecvPtr = mRecvDataBuf;
        if(theRecvPtr == NULL || strstr(theRecvPtr,ack) == NULL)
        {
            ret = 1;
        }
        else
        {
            ret = 0;
        }
        Esp8266RecvClear();
    #endif
    }
    return ret;
}

#if 0
/**
  * @brief  Esp8266 connect to server
  * @param  type:TCP/UDP
  *         ip:IP adress
  *         port:Port
  * @retval 0:Success 1:Fail
  */
uint8_t  Esp8266ConnectServer(const uint8_t *type , const uint8_t *ip , const uint32_t port)
{
    uint8_t ret = 0xFF;
    uint8_t theSendPtr[100] = {0};
    sprintf(theSendPtr,"AT+CIPSTART=\"%s\",\"%s\",%d",type,ip,port);
    //uint8_t *theSendPtr = "AT+CIPSTART="TCP\",\"192.168.1.100\",8080";
    ret = Esp8266SendCmd(theSendPtr,"OK");
    return ret;
}

/**
  * @brief  Esp8266 set to enable passthrough mode
  * @param  mode:0/1
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetTransMode(uint8_t mode)
{
    uint8_t ret = 0xFF;
    if(mode == 1)
    {
        ret = Esp8266SendCmd("AT+CIPMODE=1","OK");
    }
    else
    {
        ret = Esp8266SendCmd("AT+CIPMODE=0","OK");
    }
    return ret;
}

/**
  * @brief  Esp8266 set to passthrough mode
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266StartTransmission(void)
{
    uint8_t ret = 0xFF;
    ret = Esp8266SendCmd("AT+CIPSEND","OK");
    return ret;
}

/**
  * @brief  Esp8266 quit passthrough mode
  * @param  None
  * @retval None
  */
void Esp8266QuitTransmission(void)
{
    Esp8266SendCmd("+++",NULL);
}

/**
  * @brief  Esp8266 disconnect server
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266DisableConnect(void)
{
    uint8_t ret = 0xFF;
    ret = Esp8266SendCmd("AT+CIPCLOSE","OK");
    return ret;
}
#endif

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
