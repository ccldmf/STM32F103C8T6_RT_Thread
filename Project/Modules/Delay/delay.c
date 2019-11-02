/**
  ******************************************************************************
  * @file    Modules/Delay/delay.c
  * @author  CC
  * @version V1.0.0
  * @date    02-11-2019
  * @brief   STM32F103C8T6 development board delay control
  *          This file provides delay processing control
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "delay.h"

/**
  * @brief  This function set delay time.
  * @param  nCount:delay value.
  * @retval None
  */
void Delay(uint32_t nCount)
{
    for(; nCount != 0; nCount--);
}

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
