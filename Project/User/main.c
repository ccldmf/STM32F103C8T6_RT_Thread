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
#include <stdio.h>
#include "systemConfigure.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#ifdef ENABLE_DHT11_MODULE
#include "dht11.h"
#endif
#ifdef ENABLE_RC522_MODULE
#include "rc522.h"
#endif
#ifdef ENABLE_LCD_MODULE
#include "lcd.h"
#ifdef USING_GUI
#include "GUI.h"
#endif
#endif
#ifdef ENABLE_TEST_MODULE
#include "SampleTest.h"
#endif

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
#ifdef ENABLE_DHT11_MODULE
    DHT11_Init();
#endif
#ifdef ENABLE_RC522_MODULE
    RC522_Init ();
    RC522_Reset();
    RC522_ConfigType( 'A' );
#endif
#ifdef ENABLE_LCD_MODULE
    Lcd_Init();
    Lcd_BLK_Turn_On();
#endif
    printf("************************************\n");
    printf("*          Smart House Iinit       *\n");
    printf("************************************\n");

    while(1)
    {
#ifdef ENABLE_TEST_MODULE
    SampleTest();
#endif
    LED_On();
    Delay_ms(100);
    LED_Off();
    Delay_ms(100);

    }
}

