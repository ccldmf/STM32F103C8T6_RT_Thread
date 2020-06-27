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
#include <stdio.h>
#include "delay.h"
#include "systemConfigure.h"

#ifdef USING_SPI
#if !defined (USING_SPI1) && !defined (USING_SPI2)
 #error "Please select a SPI port to send or read data."
#endif

#ifdef USING_SPI1
/********************************* SPI1 define functions **********************/
#define    SPI1_SCK_LOW()      GPIO_ResetBits( SPI1_GPIO_SCK_PORT , SPI1_GPIO_SCK_PIN )
#define    SPI1_SCK_HIGH()     GPIO_SetBits( SPI1_GPIO_SCK_PORT , SPI1_GPIO_SCK_PIN )
#define    SPI1_MOSI_LOW()     GPIO_ResetBits( SPI1_GPIO_MOSI_PORT , SPI1_GPIO_MOSI_PIN )
#define    SPI1_MOSI_HIGH()    GPIO_SetBits( SPI1_GPIO_MOSI_PORT , SPI1_GPIO_MOSI_PIN )
#define    SPI1_MISO_GET()     GPIO_ReadInputDataBit( SPI1_GPIO_MISO_PORT , SPI1_GPIO_MISO_PIN )

/**
  * @brief  SPI1 bus init
  * @param  None
  * @retval None
  */
static void SPI1_Init( void );

/**
  * @brief  SPI1 send byte
  * @param  aByte: Send data
  * @retval None
  */
static void SPI1_SendByte( uint8_t aByte );

/**
  * @brief  SPI1 send byte
  * @param  None
  * @retval Read byte
  */
static uint8_t SPI1_ReadByte( void );

#endif

#ifdef USING_SPI2
/********************************* SPI2 define functions **********************/
#define    SPI2_SCK_LOW()      GPIO_ResetBits( SPI2_GPIO_SCK_PORT , SPI2_GPIO_SCK_PIN )
#define    SPI2_SCK_HIGH()     GPIO_SetBits( SPI2_GPIO_SCK_PORT , SPI2_GPIO_SCK_PIN )
#define    SPI2_MOSI_LOW()     GPIO_ResetBits( SPI2_GPIO_MOSI_PORT , SPI2_GPIO_MOSI_PIN )
#define    SPI2_MOSI_HIGH()    GPIO_SetBits( SPI2_GPIO_MOSI_PORT , SPI2_GPIO_MOSI_PIN )
#define    SPI2_MISO_GET()     GPIO_ReadInputDataBit( SPI2_GPIO_MISO_PORT , SPI2_GPIO_MISO_PIN )

/**
  * @brief  SPI2 bus init
  * @param  None
  * @retval None
  */
static void SPI2_Init( void );

/**
  * @brief  SPI2 send byte
  * @param  aByte: Send data
  * @retval None
  */
static void SPI2_SendByte( uint8_t aByte );

/**
  * @brief  SPI2 send byte
  * @param  None
  * @retval Read byte
  */
static uint8_t SPI2_ReadByte( void );
#endif

/**
  * @brief  SPI Init
  * @param  aPort: SPI port
  * @retval None
  */
void SPIx_Init( SPI_PORT aPort )
{
    if( SPI1_PORT == aPort )
    {
    #ifdef USING_SPI1
        SPI1_Init();
    #else
        printf("Error! Need enable SPI1.\n");
    #endif
    }
    else if( SPI2_PORT == aPort )
    {
    #ifdef USING_SPI2
        SPI2_Init();
    #else
        printf("Error! Need enable SPI1.\n");
    #endif
    }
}

/**
  * @brief  SPI send byte
  * @param  aPort: SPI port
  * @param  aByte: Send data
  * @retval None
  */
void SPI_SendByte( SPI_PORT aPort , uint8_t aByte )
{
    if( SPI1_PORT == aPort )
    {
        #ifdef USING_SPI1
        SPI1_SendByte( aByte );
        #endif
    }
    else if( SPI2_PORT == aPort )
    {
        #ifdef USING_SPI2
        SPI2_SendByte( aByte );
        #endif
    }
    else
    {
        printf("Error! Not suport SPI port.\n");
    }
}

/**
  * @brief  SPI send byte
  * @param  aPort: SPI port
  * @retval Read byte
  */
uint8_t SPI_ReadByte( SPI_PORT aPort )
{
    uint8_t theReadData;

    if( SPI1_PORT == aPort )
    {
        #ifdef USING_SPI1
        theReadData = SPI1_ReadByte();
        #endif
    }
    else if( SPI2_PORT == aPort )
    {
        #ifdef USING_SPI2
        theReadData = SPI2_ReadByte();
        #endif
    }
    else
    {
        printf("Error! Not support SPI port.\n");
        return NULL;
    }
    return theReadData;
}

#ifdef USING_SPI1
/**
  * @brief  SPI1 bus init
  * @param  None
  * @retval None
  */
static void SPI1_Init( void )
{
    /* SPI_InitTypeDef  SPI_InitStructure */
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Configure SPI1 pins: SCK */
    SPI1_GPIO_SCK_CLK_FUN( SPI1_GPIO_SCK_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = SPI1_GPIO_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = SPI1_GPIO_SCK_Mode;
    GPIO_Init( SPI1_GPIO_SCK_PORT , &GPIO_InitStructure );

    /*!< Configure SPI1 pins: MOSI */
    SPI1_GPIO_MOSI_CLK_FUN( SPI1_GPIO_MOSI_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = SPI1_GPIO_MOSI_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = SPI1_GPIO_MOSI_Mode;
    GPIO_Init( SPI1_GPIO_MOSI_PORT , &GPIO_InitStructure );

    /*!< Configure SPI1 pins: MISO */
    SPI1_GPIO_MISO_CLK_FUN( SPI1_GPIO_MISO_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = SPI1_GPIO_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = SPI1_GPIO_MISO_Mode;
    GPIO_Init( SPI1_GPIO_MISO_PORT , &GPIO_InitStructure );
}

/**
  * @brief  SPI1 send byte
  * @param  aByte: Send data
  * @retval None
  */
static void SPI1_SendByte( uint8_t aByte )
{
    uint8_t i;

    for( i = 0 ; i < 8 ; i++ )
    {
        if( aByte & 0x80 )
        {
            SPI1_MOSI_HIGH();
        }
        else
        {
            SPI1_MOSI_LOW();
        }
        Delay_us( 2 );

        SPI1_SCK_LOW();
        Delay_us( 2 );

        SPI1_SCK_HIGH();
        Delay_us( 2 );

        aByte <<= 1;
    }
}

/**
  * @brief  SPI1 send byte
  * @param  None
  * @retval Read byte
  */
static uint8_t SPI1_ReadByte( void )
{
    uint8_t i , theReadData;

    for( i = 0 ; i < 8 ; i++ )
    {
        theReadData <<= 1;
        SPI1_SCK_LOW();

        Delay_us( 2 );
        if( SPI1_MISO_GET() == 1 )
        {
            theReadData |= 0x01;
        }

        Delay_us( 2 );
        SPI1_SCK_HIGH();
        Delay_us( 2 );
    }
    return theReadData;
}

#endif

#ifdef USING_SPI2
/**
  * @brief  SPI2 bus init
  * @param  None
  * @retval None
  */
static void SPI2_Init( void )
{
    /* SPI_InitTypeDef  SPI_InitStructure */
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Configure SPI2 pins: SCK */
    SPI2_GPIO_SCK_CLK_FUN( SPI2_GPIO_SCK_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = SPI2_GPIO_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = SPI2_GPIO_SCK_Mode;
    GPIO_Init( SPI2_GPIO_SCK_PORT , &GPIO_InitStructure );

    /*!< Configure SPI2 pins: MOSI */
    SPI2_GPIO_MOSI_CLK_FUN( SPI2_GPIO_MOSI_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = SPI2_GPIO_MOSI_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = SPI2_GPIO_MOSI_Mode;
    GPIO_Init( SPI2_GPIO_MOSI_PORT , &GPIO_InitStructure );

    /*!< Configure SPI2 pins: MISO */
    SPI2_GPIO_MISO_CLK_FUN( SPI2_GPIO_MISO_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = SPI2_GPIO_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = SPI2_GPIO_MISO_Mode;
    GPIO_Init( SPI2_GPIO_MISO_PORT , &GPIO_InitStructure );
}

/**
  * @brief  SPI2 send byte
  * @param  aByte: Send data
  * @retval None
  */
static void SPI2_SendByte( uint8_t aByte )
{
    uint8_t i;

    for( i = 0 ; i < 8 ; i++ )
    {
        if( aByte & 0x80 )
        {
            SPI2_MOSI_HIGH();
        }
        else
        {
            SPI2_MOSI_LOW();
        }
        Delay_us( 2 );

        SPI2_SCK_LOW();
        Delay_us( 2 );

        SPI2_SCK_HIGH();
        Delay_us( 2 );

        aByte <<= 1;
    }
}

/**
  * @brief  SPI2 send byte
  * @param  None
  * @retval Read byte
  */
static uint8_t SPI2_ReadByte( void )
{
    uint8_t i , theReadData;

    for( i = 0 ; i < 8 ; i++ )
    {
        theReadData <<= 1;
        SPI2_SCK_LOW();

        Delay_us( 2 );
        if( SPI2_MISO_GET() == 1 )
        {
            theReadData |= 0x01;
        }

        Delay_us( 2 );
        SPI2_SCK_HIGH();
        Delay_us( 2 );
    }
    return theReadData;
}
#endif

#endif /* USING_SPI */

