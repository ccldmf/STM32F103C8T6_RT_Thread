/**
  ******************************************************************************
  * @file    Modules/GUI/GUI.h
  * @author  CC
  * @version V1.0.0
  * @date    07-25-2020
  * @brief   This file provider the GUI module public API interface.
  *
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GUI_H
#define __GUI_H

#ifdef __cplusplus
    extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#ifdef USING_GUI

/**
  * @brief  Draw circle
  * @param  aX: Position x
  * @param  aY: Position y
  * @param  aRadius: Circle radius
  * @param  aColor: Cicle Color
  * @retval None
  */
void Gui_Circle( uint16_t aX , uint16_t aY , uint16_t aRadius , uint16_t aColor ); 

/**
  * @brief  Draw line
  * @param  aStartX: Start x
  * @param  aStartY: Start y
  * @param  aEndX: End x
  * @param  aEndY: End y
  * @param  aColor: Cicle Color
  * @retval None
  */
void Gui_DrawLine( uint16_t aStartX , uint16_t aStartY , uint16_t aEndX , uint16_t aEndY , uint16_t aColor );  

/**
  * @brief  Draw down button
  * @param  aStartX: Start x
  * @param  aStartY: Start y
  * @param  aEndX: End x
  * @param  aEndY: End y
  * @retval None
  */
void GUI_DrawButtonDown( uint16_t aStartX , uint16_t aStartY , uint16_t aEndX , uint16_t aEndY );

/**
  * @brief  Draw up button
  * @param  aStartX: Start x
  * @param  aStartY: Start y
  * @param  aEndX: End x
  * @param  aEndY: End y
  * @retval None
  */
void GUI_DrawButtonUp( uint16_t aStartX , uint16_t aStartY , uint16_t aEndX , uint16_t aEndY );

/**
  * @brief  Draw font
  * @param  aX: x position
  * @param  aY: y position
  * @param  aFontColor: font color
  * @param  aBackgroundColor: background color
  * @param	aString: string
  * @retval None
  */
void Gui_DrawFont_GBK16( uint16_t aX , uint16_t aY , uint16_t aFontColor , uint16_t aBackgroundColor , uint8_t *aString );

/**
  * @brief  Draw number
  * @param  aX: Position x
  * @param  aY: Position y
  * @param  aNumColor: number color
  * @param  aBackgrounColor: background color
  * @param  aNum: number
  * @retval None
  */
void GUI_DrawNum( uint16_t aX , uint16_t aY , uint16_t aNumColor , uint16_t aBackgrounColor , uint16_t aNum ) ;

/**
  * @brief  Draw number
  * @param  aImageWidth: image width
  * @param  aImageHigh: image high
  * @param  aImage: image data
  * @retval None
  */
void GUI_DrawImage( uint16_t aImageWidth , uint16_t aImageHigh , const unsigned char *aImage );

#endif /* USING_GUI */

#ifdef __cplusplus
}
#endif

#endif /* __GUI_H */


