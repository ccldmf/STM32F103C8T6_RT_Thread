/**
  ******************************************************************************
  * @file    Modules/Bigiot/bigiot.c
  * @author  CC
  * @version V1.0.0
  * @date    16-11-2019
  * @brief   STM32F103C8T6 development board for use Bigiot module.
  *          This file provides control the Bigiot on the STM32F103C8T6 development
  *          board.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bigiot.h"
#include "esp8266.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief  Device Login
 * @param  id:Device ID  apikey:Device Key
 * @retval None
 */
void BigiotLogin(const u8 *id,const u8 *apikey)
{
    uint8_t theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"checkin\",\"ID\":\"%s\",\"K\":\"%s\"}",id,apikey);

    Esp8266SendData(theSendPtr,NULL);
}

/**
 * @brief  Bigiot Send Data
 * @param  id:Device ID  data_id:Data port value:value
 * @retval None
 */
void BigiotSendData(const u8 *id,const u8 *data_id,const u8 *value)
{
    uint8_t theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%s\"}}",id,data_id,value);

    Esp8266SendData(theSendPtr,NULL);
}

/**
 * @brief  Bigiot Recv Data
 * @param  buf:Recv Buffer  len:recv data length
 * @retval value:The received data length
 */
int BigiotRecvData(u8 *data,uint32_t len)
{
    int ret = 0;
    return ret;
}

/**
 * @brief  Check whether the device or user is online
 * @param  id:Device id or User id
 * @retval None
 */
void BigiotIsOnLine(const u8 *id)
{
    uint8_t theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"isOL\",\"ID\":[\"%s\"]}",id);

    Esp8266SendData(theSendPtr,NULL);
}

/**
 * @brief  Check current device status
 * @param  None
 * @retval None
 */
void BigiotStatus(void)
{
    uint8_t theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"status\"}");

    Esp8266SendData(theSendPtr,NULL);
}

/**
 * @brief  Check server time
 * @param  None
 * @retval None
 */
void BigiotTime(void)
{
    uint8_t theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"time\",\"F\":\"Y-m-d H:i:s\"}");

    Esp8266SendData(theSendPtr,NULL);
}

/**
 * @brief  Send alarm message
 * @param  id:device id message:Alarm message
 * @retval None
 */
void BigiotAlertMessage(const u8 *id,const u8 *message)
{
    uint8_t theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"alert\",\"ID\":\"%s\",\"C\":\"%s\"}",id,message);

    Esp8266SendData(theSendPtr,NULL);
}

/**
 * @brief  Device logout
 * @param  id:Device id apikey:Device Key
 * @retval None
 */
void BigiotLogout(const char *id,const char *apikey)
{
    uint8_t theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"checkout\",\"ID\":\"%s\",\"K\":\"%s\"}",id,apikey);

    Esp8266SendData(theSendPtr,NULL);
}

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
