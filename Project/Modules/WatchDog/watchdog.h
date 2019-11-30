/**
  ******************************************************************************
  * @file    Modules/WatchDog/watchdog.h
  * @author  CC
  * @version V1.0.0
  * @date    26-11-2019
  * @brief   This file contains the headers of the WWDG handlers.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

#ifndef _WATCH_DOG_H
#define _WATCH_DOG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/**
  * @brief  Independent Watch Dog Init
  * @param  None
  * @retval None
  */
void IWDG_Init( void );

/**
  * @brief  Independent Watch Dog Feed
  * @param  None
  * @retval None
  */
void IWDG_Feed( void );

/**
  * @brief  Window Watch Dog Init
  * @param  None
  * @retval None
  */
void WWDG_Init( void );

/**
  * @brief  Window Watch Dog Feed
  * @param  None
  * @retval None
  */
void WWDG_Feed( void );

#endif /* __WATCH_DOG_H */

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
