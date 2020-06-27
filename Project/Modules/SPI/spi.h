/**
  ******************************************************************************
  * @file    Modules/SPI/spi.h
  * @author  CC
  * @version V1.0.0
  * @date    06-19-2020
  * @brief   This file provider the spi bus public API.
  *
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H

#ifdef __cplusplus
    extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

typedef enum
{
    SPI1_PORT ,
    SPI2_PORT
}SPI_PORT;

/**
  * @brief  SPI Init
  * @param  aPort: SPI port
  * @retval None
  */
void SPIx_Init( SPI_PORT aPort );

/**
  * @brief  SPI send byte
  * @param  aPort: SPI port
  * @param  aByte: Send data
  * @retval None
  */
void SPI_SendByte( SPI_PORT aPort , uint8_t aByte );

/**
  * @brief  SPI send byte
  * @param  aPort: SPI port
  * @retval Read byte
  */
uint8_t SPI_ReadByte( SPI_PORT aPort );

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H */
