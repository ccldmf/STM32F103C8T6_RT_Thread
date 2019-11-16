/**
  ******************************************************************************
  * @file    Modules/ESP8266/esp8266.h
  * @author  CC
  * @version V1.0.0
  * @date    03-11-2019
  * @brief   This file contains the headers of the ESP8266 module handlers.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _ESP8266_H
#define _ESP8266_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_usart.h"

#if 0
#define COMMAND(cmd1) (cmd1##"\r\n")
#define RECV_BUF_SIZE               300
#define WAIT_RECV_DATA_TIME_COUNT   200

enum WIFIMODE
    {
    WIFI_STATION = 1,
    WIFI_AP,
    WIFI_AP_STATION,
    WIFI_ERROR = -1
    };

/**
  * @brief  Esp8266 Init
  * @param  None
  * @retval None
  */
uint8_t Esp8266Init(void);

/**
 * @brief  Esp8266 Close
 * @param  None
 * @retval None
 */
uint8_t Esp8266Close(void);

/**
* @brief  Esp8266 Send Command
* @param  cmd:Command
*         ack:Expected return data.
* @retval 0:Success 1:Fail
*/
uint8_t Esp8266SendCmd(const uint8_t *cmd,const uint8_t *ack);

/**
  * @brief  Esp8266 recv usart data
  * @param  ndata:Recved data
  * @retval None
  */
void Esp8266RecvData(u8 ndata);

/**
  * @brief  Esp8266 restart
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266Reseat(void);

/**
  * @brief  Esp8266 echo function set
  * @param  flag: 1 or 0
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetReturnDisplay(unsigned char);

/**
  * @brief  Esp8266 reset factory data
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266ResetFactoryData(void);

/**
  * @brief  Esp8266 set mode
  * @param  mode: 1/2/3
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetMode(enum WIFIMODE mode);

 /**
  * @brief  Esp8266 set DHCP
  * @param
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetDHCP(u8 mode,u8 enable);

/**
  * @brief  Esp8266 set connect router
  * @param  ssid: Router name
  *         password: Router password
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetRouter(const uint8_t *ssid , const uint8_t *password);

/**
  * @brief  Esp8266 disconnect router
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266QuitRouterAPConnect(void);

/**
  * @brief  Esp8266 Set STA boot auto connection
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetSTAAutoConnect(void);
#endif

/**
  * @brief  Esp8266 send data
  * @param  data:send data
  *         ack:response data
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SendData(const uint8_t *data , const uint8_t *ack);

#if 0
/**
  * @brief  Esp8266 connect to server
  * @param  type:TCP/UDP
  *         ip:IP adress
  *         port:Port
  * @retval 0:Success 1:Fail
  */
uint8_t  Esp8266ConnectServer(const uint8_t *type , const uint8_t *ip , const uint32_t port);

/**
  * @brief  Esp8266 set to enable passthrough mode
  * @param  mode:0/1
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266SetTransMode(uint8_t mode);

/**
  * @brief  Esp8266 set to passthrough mode
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266StartTransmission(void);

/**
  * @brief  Esp8266 quit passthrough mode
  * @param  None
  * @retval None
  */
void Esp8266QuitTransmission(void);

/**
  * @brief  Esp8266 disconnect server
  * @param  None
  * @retval 0:Success 1:Fail
  */
uint8_t Esp8266DisableConnect(void);
#endif

#ifdef __cplusplus
}
#endif

#endif  /* _ESP8266_H */

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
