/**
  ******************************************************************************
  * @file    Modules/Flash/flash.h
  * @author  CC
  * @version V1.0.0
  * @date    29-11-2019
  * @brief   This file contains the headers of the flash handlers.
  ******************************************************************************
  * @attention
  *
  * STM32f103C8T6 64KB FLASH，20KB RAM，each sector size is 1KB,Program start address:0x8000000
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_H
#define __FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/**
  * @brief  Read data from flash
  * @param  addr:Read data address
  *         data:Read falsh data to save this parameter
  *         len :Read data length
  * @retval 0:Successful 1:Fail
  */
int ReadFlash( const uint32_t addr , uint8_t *data , const uint32_t len );

/**
  * @brief  Write data from flash
  * @param  addr:Write data address
  *         data:Write data to flash
  *         len :Write data length
  * @retval 0:Successful other:Success write data len
  */
int WriteFlash( const uint32_t addr , const uint8_t *data , const uint32_t len );

/**
  * @brief  Erase data
  * @param  addr:Erase data address
  *         len :Erase data length
  * @retval 0:Successful 1:Fail
  */
int EraseFlash( const uint32_t addr , const uint32_t len );

#ifdef __cplusplus
}
#endif

#endif /* __DHT11_H */

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
