/**
  ******************************************************************************
  * @file    Modules/LCD/lcd.c
  * @author  CC
  * @version V1.0.0
  * @date    06-29-2020
  * @brief   This file provider the feature of LCD module.
  *
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lcd.h"
#include "spi.h"
#include "delay.h"
#include "spi.h"

#ifdef ENABLE_LCD_MODULE

#define LCD_CS_HIGH     GPIO_SetBits( SPI1_GPIO_MISO_PORT , SPI1_GPIO_MISO_PIN )
#define LCD_CS_LOW      GPIO_ResetBits( SPI1_GPIO_MISO_PORT , SPI1_GPIO_MISO_PIN )

#define LCD_RST_HIGH    GPIO_SetBits( LCD_GPIO_RST_PORT , LCD_GPIO_RST_PIN )
#define LCD_RST_LOW     GPIO_ResetBits( LCD_GPIO_RST_PORT , LCD_GPIO_RST_PIN )

#define LCD_DC_HIGH     GPIO_SetBits( LCD_GPIO_DC_PORT , LCD_GPIO_DC_PIN )
#define LCD_DC_LOW      GPIO_ResetBits( LCD_GPIO_DC_PORT , LCD_GPIO_DC_PIN )

/**
  * @brief  LCD RST pin configure
  * @param  None
  * @retval None
  */
static void LCD_RST_Configure( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    LCD_GPIO_RST_CLK_FUN( LCD_GPIO_RST_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = LCD_GPIO_RST_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = LCD_GPIO_RST_Mode;
    GPIO_Init( LCD_GPIO_RST_PORT , &GPIO_InitStructure );
}

/**
  * @brief  LCD DC pin configure
  * @param  None
  * @retval None
  */
static void LCD_DC_Configure( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    LCD_GPIO_DC_CLK_FUN( LCD_GPIO_DC_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = LCD_GPIO_DC_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = LCD_GPIO_DC_Mode;
    GPIO_Init( LCD_GPIO_DC_PORT , &GPIO_InitStructure );
}

/**
  * @brief  LCD BLD pin configure
  * @param  None
  * @retval None
  */
static void LCD_BLD_Configure( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    LCD_GPIO_BLD_CLK_FUN( LCD_GPIO_BLD_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = LCD_GPIO_BLD_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = LCD_GPIO_BLD_Mode;
    GPIO_Init( LCD_GPIO_BLD_PORT , &GPIO_InitStructure );
}

/**
  * @brief  LCD write a index
  * @param  aIndex: index
  * @retval None
  */
static void Lcd_WriteIndex( uint8_t aIndex )
{
    LCD_CS_LOW;
    LCD_DC_LOW;
    SPI_SendByte( LCD_USING_SPI , aIndex );
    LCD_CS_HIGH;
}

/**
  * @brief  LCD write a data
  * @param  aData: data
  * @retval None
  */
static void Lcd_WriteData( uint8_t aData )
{
   LCD_CS_LOW;
   LCD_DC_HIGH;
   SPI_SendByte( LCD_USING_SPI , aData );
   LCD_CS_HIGH;
}

/**
  * @brief  LCD Init
  * @param  None
  * @retval None
  */
void Lcd_Init( void )
{
    SPIx_Init( LCD_USING_SPI );
    LCD_RST_Configure();
    LCD_DC_Configure();
    LCD_BLD_Configure();
    Lcd_Reset(); //Reset before LCD Init.

    //LCD Init For 1.44Inch LCD Panel with ST7735R.
    Lcd_WriteIndex( 0x11 );//Sleep exit
    Delay_ms( 120 );

    //ST7735R Frame Rate
    Lcd_WriteIndex( 0xB1 );
    Lcd_WriteData( 0x01 );
    Lcd_WriteData( 0x2C );
    Lcd_WriteData( 0x2D );

    Lcd_WriteIndex( 0xB2 );
    Lcd_WriteData( 0x01 );
    Lcd_WriteData( 0x2C );
    Lcd_WriteData( 0x2D );

    Lcd_WriteIndex( 0xB3 );
    Lcd_WriteData( 0x01 );
    Lcd_WriteData( 0x2C );
    Lcd_WriteData( 0x2D );
    Lcd_WriteData( 0x01);
    Lcd_WriteData( 0x2C );
    Lcd_WriteData( 0x2D );

    Lcd_WriteIndex( 0xB4 ); //Column inversion
    Lcd_WriteData( 0x07 );

    //ST7735R Power Sequence
    Lcd_WriteIndex( 0xC0 );
    Lcd_WriteData( 0xA2 );
    Lcd_WriteData( 0x02 );
    Lcd_WriteData( 0x84 );
    Lcd_WriteIndex( 0xC1 );
    Lcd_WriteData( 0xC5 );

    Lcd_WriteIndex( 0xC2 );
    Lcd_WriteData( 0x0A );
    Lcd_WriteData( 0x00 );

    Lcd_WriteIndex( 0xC3 );
    Lcd_WriteData( 0x8A );
    Lcd_WriteData( 0x2A );
    Lcd_WriteIndex( 0xC4 );
    Lcd_WriteData( 0x8A );
    Lcd_WriteData( 0xEE );

    Lcd_WriteIndex( 0xC5 ); //VCOM
    Lcd_WriteData( 0x0E );

    Lcd_WriteIndex( 0x36 ); //MX, MY, RGB mode
    Lcd_WriteData( 0xC0 );

    //ST7735R Gamma Sequence
    Lcd_WriteIndex( 0xe0 );
    Lcd_WriteData( 0x0f );
    Lcd_WriteData( 0x1a );
    Lcd_WriteData( 0x0f );
    Lcd_WriteData( 0x18 );
    Lcd_WriteData( 0x2f );
    Lcd_WriteData( 0x28 );
    Lcd_WriteData( 0x20 );
    Lcd_WriteData( 0x22 );
    Lcd_WriteData( 0x1f );
    Lcd_WriteData( 0x1b );
    Lcd_WriteData( 0x23 );
    Lcd_WriteData( 0x37 );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( 0x07 );
    Lcd_WriteData( 0x02 );
    Lcd_WriteData( 0x10 );

    Lcd_WriteIndex( 0xe1 );
    Lcd_WriteData( 0x0f );
    Lcd_WriteData( 0x1b );
    Lcd_WriteData( 0x0f );
    Lcd_WriteData( 0x17 );
    Lcd_WriteData( 0x33 );
    Lcd_WriteData( 0x2c );
    Lcd_WriteData( 0x29 );
    Lcd_WriteData( 0x2e );
    Lcd_WriteData( 0x30 );
    Lcd_WriteData( 0x30 );
    Lcd_WriteData( 0x39 );
    Lcd_WriteData( 0x3f );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( 0x07 );
    Lcd_WriteData( 0x03 );
    Lcd_WriteData( 0x10 );

    Lcd_WriteIndex( 0x2a );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( 0x7f );

    Lcd_WriteIndex( 0x2b );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( 0x9f );

    Lcd_WriteIndex( 0xF0 ); //Enable test command
    Lcd_WriteData( 0x01 );
    Lcd_WriteIndex( 0xF6 ); //Disable ram power save mode
    Lcd_WriteData( 0x00 );

    Lcd_WriteIndex( 0x3A ); //65k mode
    Lcd_WriteData( 0x05 );

    Lcd_WriteIndex( 0x29 ); //Display on
}

/**
  * @brief  LCD Reset
  * @param  None
  * @retval None
  */
void Lcd_Reset( void )
{
    LCD_RST_LOW;
    Delay_ms( 100 );
    LCD_RST_HIGH;
    Delay_ms( 50 );
}

/**
  * @brief  LCD set color
  * @param  aColor: Color
  * @retval None
  */
void Lcd_SetColor( uint16_t aColor )
{
    unsigned int i , m;
    Lcd_SetRegion( 0 , 0 , LCD_WIDTH - 1 , LCD_HEIGHT - 1 );
    Lcd_WriteIndex( 0x2C );
    for( i = 0 ; i < LCD_WIDTH ; i++ )
    {
        for( m = 0 ; m < LCD_HEIGHT ; m++ )
        {
            LCD_DrawAWord( aColor );
        }
    }
}

/**
  * @brief  LCD draw point
  * @param  aX: x position
  * @param  aY: y position
  * @param  aColor: color
  * @retval None
  */
void Lcd_DrawPoint( uint16_t aX , uint16_t aY , uint16_t aColor )
{
    Lcd_SetRegion( aX , aY , aX + 1 , aY + 1 );
    LCD_DrawAWord( aColor );
}

/**
  * @brief  LCD draw a word
  * @param  aData: data
  * @retval None
  */
void LCD_DrawAWord( uint16_t aData )
{
    LCD_CS_LOW;
    LCD_DC_HIGH;
    SPI_SendByte( LCD_USING_SPI , aData >> 8 );
    SPI_SendByte( LCD_USING_SPI , aData );
    LCD_CS_HIGH;
}

/**
  * @brief  LCD backlight turn on
  * @param  None
  * @retval None
  */
void Lcd_BLK_Turn_On( void )
{
    GPIO_SetBits( LCD_GPIO_BLD_PORT , LCD_GPIO_BLD_PIN );
}

/**
  * @brief  LCD backlight turn off
  * @param  None
  * @retval None
  */
void Lcd_BLK_Turn_Off( void )
{
    GPIO_ResetBits( LCD_GPIO_BLD_PORT , LCD_GPIO_BLD_PIN );
}

/**
  * @brief  LCD display area
  * @param  aStartX: start x position
  * @param  aStartY: start y position
  * @param  aEndX: end x position
  * @param  aEndY: end y position
  * @retval None
  */
void Lcd_SetRegion( uint16_t aStartX , uint16_t aStartY , uint16_t aEndX , uint16_t aEndY )
{
    Lcd_WriteIndex( 0x2a );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( aStartX );//Lcd_WriteData(x_start+2);
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( aEndX + 2 );

    Lcd_WriteIndex( 0x2b );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( aStartY + 0 );
    Lcd_WriteData( 0x00 );
    Lcd_WriteData( aEndY + 1 );

    Lcd_WriteIndex( 0x2c );
}

/**
  * @brief  LCD read value
  * @param  aX: x position
  * @param  aY: y position
  * @retval value
  */
int Lcd_ReadPoint( uint16_t aX , uint16_t aY )
{
    unsigned int aData;
    Lcd_SetRegion( aX , aY , aX , aY );

    Lcd_WriteData( aData );
    return aData;
}

#endif /* ENABLE_LCD_MODULE */

