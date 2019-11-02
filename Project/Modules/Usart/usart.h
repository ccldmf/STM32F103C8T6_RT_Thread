/**
  ******************************************************************************
  * @file    Modules/Usart/usart.h
  * @author  CC
  * @version V1.0.0
  * @date    02-11-2019
  * @brief   This file contains the headers of the USART handlers.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

void USART_Configuration(USART_TypeDef* USARTx , uint32_t nBaudRate);

#ifdef __cplusplus
}
#endif

#endif /* __USART_H */

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
