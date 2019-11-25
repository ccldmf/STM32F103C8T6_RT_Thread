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
#include "dht11.h"
#include <stdio.h>

/**
  * @brief  Application.
  * @param  None
  * @retval None
  */
int main(void)
{
    uint32_t theHighValue,theLowValue;
    uint32_t theTmp;
    SystemInit();
    LED_Init();
    Delay_Init();
    USART_Configuration(USART1,115200);
    USART_Configuration(USART2,115200);
    USART_Configuration(USART3,115200);
    DHT11_Init();
    printf("************************************\n");
    printf("*          Smart House Iinit       *\n");
    printf("************************************\n");


    while (1)
    {

        LED_On();
        Delay_ms(100);
        LED_Off();
        Delay_ms(100);
        DHT11_ReadData();
        theTmp = DHT11_GetTem();
        printf("Tem = %d.%d\n" , (theTmp>>8) , (theTmp&0xFF));
        theTmp = DHT11_GetHum();
        printf("Hum = %d.%d\n" , (theTmp>>8) , (theTmp&0xFF));
        Delay_ms(1500);
    }
}





