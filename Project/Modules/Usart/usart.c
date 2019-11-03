/**
  ******************************************************************************
  * @file    Modules/Usart/usart.c
  * @author  CC
  * @version V1.0.0
  * @date    02-11-2019
  * @brief   STM32F103C8T6 development board USART control
  *          This file provides control the USART on the STM32F103C8T6 development
  *          board.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include <stdio.h>

/**
  * @brief  USART1 Init
  * @param  nBaudRate:Baudrate
  * @retval None
  */
static void USART1_Init(uint32_t nBaudRate)
{
    GPIO_InitTypeDef GPIO_InitStrue;
    USART_InitTypeDef USART_InitStrue;
    NVIC_InitTypeDef NVIC_InitStrue;

    // Enable the USART1 Pins Software Remapping
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    // Configure USART1 Rx (PA.09)
    GPIO_InitStrue.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStrue.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStrue.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&GPIO_InitStrue);

    // Configure USART2 Tx (PA.10)
    GPIO_InitStrue.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStrue.GPIO_Pin   = GPIO_Pin_10;
    GPIO_InitStrue.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA,&GPIO_InitStrue);

    // Set USART1 parameters
    USART_InitStrue.USART_BaudRate            = nBaudRate;
    USART_InitStrue.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStrue.USART_Mode                = USART_Mode_Tx|USART_Mode_Rx;
    USART_InitStrue.USART_Parity              = USART_Parity_No;
    USART_InitStrue.USART_StopBits            = USART_StopBits_1;
    USART_InitStrue.USART_WordLength          = USART_WordLength_8b;
    USART_Init(USART1,&USART_InitStrue);

    // Enable USART1
    USART_Cmd(USART1,ENABLE);
    // Open receive interrupt
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    // Set the IRQ channel
    NVIC_InitStrue.NVIC_IRQChannel = USART1_IRQn;
    // Enable the USART1 interrupt
    NVIC_InitStrue.NVIC_IRQChannelCmd = ENABLE;
    // Set interrupt priority
    NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStrue.NVIC_IRQChannelSubPriority = 1;
    // Init interrupt
    NVIC_Init(&NVIC_InitStrue);
}

/**
  * @brief  USART2 Init
  * @param  nBaudRate:Baudrate
  * @retval None
  */
static void USART2_Init(uint32_t nBaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // Enable the USART2 Pins Software Remapping
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB2Periph_AFIO, ENABLE);

    // Configure USART2 Rx (PA.03) as input floating
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Configure USART2 Tx (PA.02) as alternate function push-pull
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Enable the USART2 Interrupt
    NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_InitStructure.USART_BaudRate            = nBaudRate;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    // Enable USART2
    USART_Cmd(USART2, ENABLE);
}

/**
  * @brief  USART3 Init
  * @param  nBaudRate:Baudrate
  * @retval None
  */
static void USART3_Init(uint32_t nBaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    // Enable the USART3 Pins Software Remapping
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // Configure USART3 Rx (PB.11) as input floating
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Configure USART3 Tx (PB.10) as alternate function push-pull
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Enable the USART3 Interrupt
    NVIC_InitStructure.NVIC_IRQChannel                   = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_InitStructure.USART_BaudRate            = nBaudRate;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    // Enable USART3
    USART_Cmd(USART3, ENABLE);
}

/**
  * @brief  Configuration USART
  * @param  USARTx:USAER port
  *         nBaudRate:Baudrate
  * @retval None
  */
void USART_Configuration(USART_TypeDef* USARTx , uint32_t nBaudRate)
{
    if ( USART1 == USARTx )
    {
    USART1_Init( nBaudRate );
    }
    else if ( USART2 == USARTx )
    {
    USART2_Init( nBaudRate );
    }
    else
    {
    USART3_Init( nBaudRate );
    }
}

/**
  * @brief  Configuration USART
  * @param  USARTx:USAER port
  *         nString:data
  * @retval None
  */
void USART_SendString(USART_TypeDef* USARTx , const uint8_t *nString)
{
    uint8_t *theStringPtr = (uint8_t *)nString;
    while(*theStringPtr)
    {
        while(!USART_GetFlagStatus(USARTx,USART_FLAG_TXE));
        USART_SendData(USARTx, *theStringPtr);
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TC));
        theStringPtr++;
    }
}

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#if !defined (USART1_PRINTF) && !defined (USART2_PRINTF) && !defined (USART3_PRINTF)
    /* #define USART1_PRINTF */     /*!< USART1_PRINTF: Use USART1 for send information */
    /* #define USART2_PRINTF */     /*!< USART2_PRINTF: Use USART2 for send information */
    /* #define USART3_PRINTF */     /*!< USART3_PRINTF: Use USART3 for send information */
#endif

#if !defined (USART1_PRINTF) && !defined (USART2_PRINTF) && !defined (USART3_PRINTF)
 #error "Please select a USART for send the application information (in usart.c file)"
#endif

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    USART_TypeDef *theUSARTx;

#ifdef USART1_PRINTF
    theUSARTx = USART1;
#elif USART2_PRINTF
    theUSARTx = USART2;
#else
    theUSARTx = USART3;
#endif
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(theUSARTx, (uint8_t) ch);
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(theUSARTx, USART_FLAG_TC) == RESET)
    {}

    return ch;
}

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
