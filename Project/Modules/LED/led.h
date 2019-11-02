/**
  ******************************************************************************
  * @file    Modules/LED/LED.h
  * @author  CC
  * @version V1.0.0
  * @date    02-11-2019
  * @brief   This file contains the headers of the LED handlers.
  ******************************************************************************
  * @attention
  *
  * There is only one LED on the STM32F103C8T6 board,and it's control pin is PB12.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

void LED_Init(void);

void LED_On(void);

void LED_Off(void);

#ifdef __cplusplus
}
#endif

#endif /* __LED_H */

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
