/**
  ******************************************************************************
  * @file    Modules/Bigiot/bigiot.h
  * @author  CC
  * @version V1.0.0
  * @date    16-11-2019
  * @brief   This file contains the headers of the Bigiot module handlers.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BIGIOT_H
#define _BIGIOT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/**
 * @brief  Device Login
 * @param  id:Device ID  apikey:Device Key
 * @retval None
 */
void BigiotLogin(const u8 *id,const u8  *apikey);

/**
 * @brief  Bigiot Send Data
 * @param  id:Device ID  data_id:Data port value:value
 * @retval None
 */
void BigiotSendData(const u8  *id,const u8  *data_id,const u8  *value);

/**
 * @brief  Bigiot Recv Data
 * @param  buf:Recv Buffer  len:recv data length
 * @retval value:The received data length
 */
int BigiotRecvData(u8 *data,uint32_t len);

/**
 * @brief  Check whether the device or user is online
 * @param  id:Device id or User id
 * @retval None
 */
void BigiotIsOnLine(const u8 *id);

/**
 * @brief  Check current device status
 * @param  None
 * @retval None
 */
void BigiotStatus(void);

/**
 * @brief  Check server time
 * @param  None
 * @retval None
 */
void BigiotTime(void);

/**
 * @brief  Send alarm message
 * @param  id:device id message:Alarm message
 * @retval None
 */
void BigiotAlertMessage(const u8 *id,const u8 *message);

/**
 * @brief  Device logout
 * @param  id:Device id apikey:Device Key
 * @retval None
 */
void BigiotLogout(const u8  *,const u8  *);

#ifdef __cplusplus
}
#endif

#endif
/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
