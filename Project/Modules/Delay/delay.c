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
#include "stm32f10x_systick.h"

/* Define global parameter. --------------------------------------------------*/
// Delay time multiplier of us
static uint8_t  delay_fac_us = 0;
// Delay time multiplier of ms
static uint16_t delay_fac_ms = 0;
static FlagStatus  Status;

/**
  * @brief  Init delay
  * @param  nCount:delay value.
  * @retval None
  */
void Delay_Init(void)
{
    RCC_ClocksTypeDef RCC_ClocksStatus;

    RCC_GetClocksFreq(&RCC_ClocksStatus);
    // Select external clock   HCLK/8.
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    SysTick_ITConfig(DISABLE);
    delay_fac_us = RCC_ClocksStatus.HCLK_Frequency / 8000000;
    delay_fac_ms = RCC_ClocksStatus.HCLK_Frequency / 8000;
}

/**
  * @brief  delay us
  * @param  nus:delay value.
  * @retval None
  */
void Delay_us(uint32_t nus)
{
    // Load time
    SysTick_SetReload(delay_fac_us * nus);
    // Clear counter
    SysTick_CounterCmd(SysTick_Counter_Clear);
    // Start from bottom
    SysTick_CounterCmd(SysTick_Counter_Enable);
    do
    {
        Status = SysTick_GetFlagStatus(SysTick_FLAG_COUNT);
    }while (Status != SET);     // Wait for time arrival
    // Close counter
    SysTick_CounterCmd(SysTick_Counter_Disable);
    // Clear counter
    SysTick_CounterCmd(SysTick_Counter_Clear);
}

/**
  * @brief  delay ms
  * @param  nms:delay value.
  * @retval None
  */
void Delay_ms(uint32_t nms)
{
    uint32_t temp = delay_fac_ms * nms;

    if (temp > 0x00ffffff)
    {
        temp = 0x00ffffff;
    }
    // Load time
    SysTick_SetReload(temp);
    // Clear counter
    SysTick_CounterCmd(SysTick_Counter_Clear);
    // Start from bottom
    SysTick_CounterCmd(SysTick_Counter_Enable);
    do
    {
        Status = SysTick_GetFlagStatus(SysTick_FLAG_COUNT);
    }while (Status != SET);     // Wait for time arrival
    // Close counter
    SysTick_CounterCmd(SysTick_Counter_Disable);
    // Clear counter
    SysTick_CounterCmd(SysTick_Counter_Clear);
}

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
