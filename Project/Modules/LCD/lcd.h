/**
  ******************************************************************************
  * @file    Modules/LCD/lcd.h
  * @author  CC
  * @version V1.0.0
  * @date    06-29-2020
  * @brief   This file provider the LCD module public API interface.
  *
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
    extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "systemConfigure.h"

#ifdef ENABLE_LCD_MODULE

/**
  * @brief  LCD Init
  * @param  None
  * @retval None
  */
void Lcd_Init( void );

/**
  * @brief  LCD Reset
  * @param  None
  * @retval None
  */
void Lcd_Reset( void );

/**
  * @brief  LCD set color
  * @param  aColor: Color
  * @retval None
  */
void Lcd_SetColor( uint16_t aColor );

/**
  * @brief  LCD draw point
  * @param  aX: x position
  * @param  aY: y position
  * @param  aColor: color
  * @retval None
  */
void Lcd_DrawPoint( uint16_t aX , uint16_t aY , uint16_t aColor );

/**
  * @brief  LCD draw a word
  * @param  aData: data
  * @retval None
  */
void LCD_DrawAWord( uint16_t aData );

/**
  * @brief  LCD backlight turn on
  * @param  None
  * @retval None
  */
void Lcd_BLK_Turn_On( void );

/**
  * @brief  LCD backlight turn off
  * @param  None
  * @retval None
  */
void Lcd_BLK_Turn_Off( void );

/**
  * @brief  LCD display area
  * @param  aStartX: start x position
  * @param  aStartY: start y position
  * @param  aEndX: end x position
  * @param  aEndY: end y position
  * @retval None
  */
void Lcd_SetRegion( uint16_t aStartX , uint16_t aStartY , uint16_t aEndX , uint16_t aEndY );

/**
  * @brief  LCD read value
  * @param  aX: x position
  * @param  aY: y position
  * @retval value
  */
int Lcd_ReadPoint( uint16_t aX , uint16_t aY );

#endif /* ENABLE_LCD_MODULE */

#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */

