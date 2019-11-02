/**
  ******************************************************************************
  * @file    Modules/Delay/delay.h
  * @author  CC
  * @version V1.0.0
  * @date    02-11-2019
  * @brief   This file contains the headers of the delay handlers.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

void Delay_Init(void);

void Delay_ms(uint32_t nms);

void Delay_us(uint32_t nus);

#ifdef __cplusplus
}
#endif

#endif /* __DELAY_H */

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
