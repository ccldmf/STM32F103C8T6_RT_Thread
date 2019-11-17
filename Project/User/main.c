/**
  ******************************************************************************
  * @file    User/main.c
  * @author  CC
  * @version V1.0.0
  * @date    02-11-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "esp8266.h"
#include "bigiot.h"
#include <stdio.h>

/**
  * @brief  Application.
  * @param  None
  * @retval None
  */
int main(void)
{
    SystemInit();
    LED_Init();
    Delay_Init();
    USART_Configuration(USART1,115200);
    USART_Configuration(USART2,115200);
    USART_Configuration(USART3,115200);
    printf("************************************\n");
    printf("*          Smart House Iinit       *\n");
    printf("************************************\n");
    BigiotLogin("6757","a215adb24");

    while (1)
    {

        LED_On();
        Delay_ms(100);
        LED_Off();
        Delay_ms(100);
        Delay_ms(2000);
        BigiotSendData("6757","6033","33.5");
    }
}





