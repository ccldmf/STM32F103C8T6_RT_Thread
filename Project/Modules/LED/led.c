/**
  ******************************************************************************
  * @file    Modules/LED/LED.c
  * @author  CC
  * @version V1.0.0
  * @date    02-11-2019
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

/**
  * @brief  This function handles LED init.
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
    // Define a structure of GPIO_InitTypeDef.
    GPIO_InitTypeDef  GPIO_InitStructure;
    // Enable GPIOB periphral clock.
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    // Select the pin of use.
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    // Set the pin mode to PP mode.
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    // Set the pin speed to 50MHz.
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // Init GPIO.
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  This function set LED on.
  * @param  None
  * @retval None
  */
void LED_On(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

/**
  * @brief  This function set LED off.
  * @param  None
  * @retval None
  */
void LED_Off(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
