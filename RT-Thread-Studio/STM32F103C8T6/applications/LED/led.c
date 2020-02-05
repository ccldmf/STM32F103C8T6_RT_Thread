/**
  ******************************************************************************
  * @file    Modules/LED/led.c
  * @author  CC
  * @version V1.0.0
  * @date    02-05-2020
  * @brief   STM32F103C8T6 development board LED control
  *          This file provides control the LED on the STM32F103C8T6 development
  *          board.
  ******************************************************************************
  * @attention
  *
  * There is only one LED on the STM32F103C8T6 board,and it's control pin is PB12.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "led.h"

#define LED0_PIN    GET_PIN(B, 12)

/**
  * @brief  This function handles LED init.
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
}

/**
  * @brief  This function set LED on.
  * @param  None
  * @retval None
  */
void LED_On(void)
{
    rt_pin_write(LED0_PIN, 0);
}

/**
  * @brief  This function set LED off.
  * @param  None
  * @retval None
  */
void LED_Off(void)
{
    rt_pin_write(LED0_PIN, 1);
}
