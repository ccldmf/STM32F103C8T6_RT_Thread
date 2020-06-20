/**
  ******************************************************************************
  * @file    Modules/SPI/spi.c
  * @author  CC
  * @version V1.0.0
  * @date    06-19-2020
  * @brief   This file provider the feature spi bus.
  *
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"
#include "stm32f10x.h"
#include "systemConfigure.h"

/**
  * @brief  SPI bus init
  * @param  None
  * @retval None
  */
void SPIx_Init( void )
{
    /* SPI_InitTypeDef  SPI_InitStructure */
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Configure SPI_RC522_SPI pins: CS */
    RC522_GPIO_CS_CLK_FUN ( RC522_GPIO_CS_CLK, ENABLE );
    GPIO_InitStructure.GPIO_Pin = RC522_GPIO_CS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = RC522_GPIO_CS_Mode;
    GPIO_Init(RC522_GPIO_CS_PORT, &GPIO_InitStructure);

    /*!< Configure SPI_RC522_SPI pins: SCK */
    RC522_GPIO_SCK_CLK_FUN ( RC522_GPIO_SCK_CLK, ENABLE );
    GPIO_InitStructure.GPIO_Pin = RC522_GPIO_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = RC522_GPIO_SCK_Mode;
    GPIO_Init(RC522_GPIO_SCK_PORT, &GPIO_InitStructure);

    /*!< Configure SPI_RC522_SPI pins: MOSI */
    RC522_GPIO_MOSI_CLK_FUN ( RC522_GPIO_MOSI_CLK, ENABLE );
    GPIO_InitStructure.GPIO_Pin = RC522_GPIO_MOSI_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = RC522_GPIO_MOSI_Mode;
    GPIO_Init(RC522_GPIO_MOSI_PORT, &GPIO_InitStructure);

    /*!< Configure SPI_RC522_SPI pins: MISO */
    RC522_GPIO_MISO_CLK_FUN ( RC522_GPIO_MISO_CLK, ENABLE );
    GPIO_InitStructure.GPIO_Pin = RC522_GPIO_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = RC522_GPIO_MISO_Mode;
    GPIO_Init(RC522_GPIO_MISO_PORT, &GPIO_InitStructure);

    /*!< Configure SPI_RC522_SPI pins: RST */
    RC522_GPIO_RST_CLK_FUN ( RC522_GPIO_RST_CLK, ENABLE );
    GPIO_InitStructure.GPIO_Pin = RC522_GPIO_RST_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = RC522_GPIO_RST_Mode;
    GPIO_Init(RC522_GPIO_RST_PORT, &GPIO_InitStructure);
}


