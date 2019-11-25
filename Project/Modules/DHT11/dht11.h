/**
  ******************************************************************************
  * @file    Modules/DHT11/dht11.h
  * @author  CC
  * @version V1.0.0
  * @date    25-11-2019
  * @brief   This file contains the headers of the DHT11 handlers.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DHT11_H
#define __DHT11_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

/* Define the DHT11 pins ----------------------------------------------------**/
#define DHT11_RCC         RCC_APB2Periph_GPIOB
#define DHT11_GPIO        GPIOB
#define DHT11_GPIO_PIN    GPIO_Pin_7

/* Define the DHT11 module return data structure -----------------------------*/
typedef struct _DHT11
{
    char Tem_H;     // Integral part of temperature
    char Tem_L;     // Decimal part of Temperature
    char Hum_H;     // Integral part of humidity
    char Hum_L;     // Decimal part of humidity
}DHT11_TypeDef;

void DHT11_Init( void );

uint32_t DHT11_ReadData( void );

float DHT11_GetTem( void );

float DHT11_GetHum( void );

#ifdef __cplusplus
}
#endif

#endif /* __DHT11_H */

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
