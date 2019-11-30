/**
  ******************************************************************************
  * @file    Modules/WatchDog/watchdog.c
  * @author  CC
  * @version V1.0.0
  * @date    26-11-2019
  * @brief   This file contains the headers of the WWDG handlers.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "watchdog.h"
#include "led.h"

/*****************************************************************************
                        独立看门狗

IWDG_PRESCALER      : 分频数(0~7,只有低3位有效)
IWDG_RELOAD_VALUE   : 分频因子=4*2^IWDG_PRESCALER
Feed Dog Time       : T = ((4*2^IWDG_PRESCALER)*IWDG_RELOAD_VALUE)/40 (ms)
Sample              : T = ((4*2^4) * 625) / 40 = 1000ms = 1s
*****************************************************************************/
#define IWDG_PRESCALER          4
#define IWDG_RELOAD_VALUE       625

/*****************************************************************************
                        窗口看门狗

WWDG_WINDOW_CNT       : 计数器值
WWDG_WINDOW_VALUE     : 窗口值
WWDG_WINDOW_PRESCALER : 分频系数
*****************************************************************************/
#define WWDG_WINDOW_CNT         0x7F
#define WWDG_WINDOW_VALUE       0x5F
#define WWDG_WINDOW_PRESCALER   WWDG_Prescaler_8

/**
  * @brief  Independent Watch Dog Init
  * @param  None
  * @retval None
  */
void IWDG_Init( void )
{
    // 使能对寄存器IWDG_PR和IWDG_RLR的写操作
    IWDG_WriteAccessCmd( IWDG_WriteAccess_Enable );
    // 设置IWDG预分频值:设置IWDG预分频值
    IWDG_SetPrescaler( IWDG_PRESCALER );
    // 设置IWDG重装载值
    IWDG_SetReload( IWDG_RELOAD_VALUE );
    // 按照IWDG重装载寄存器的值重装载IWDG计数器
    IWDG_ReloadCounter();
    // 使能IWDG
    IWDG_Enable();
}

/**
  * @brief  Independent Watch Dog Feed
  * @param  None
  * @retval None
  */
void IWDG_Feed( void )
{
    IWDG_ReloadCounter();
}

/**
  * @brief  Window Watch Dog Interrupt Init
  * @param  None
  * @retval None
  */
static void WWDG_NVIC_Init( void )
{
    NVIC_InitTypeDef NVIC_InitStructure;
    // WWDG中断
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
    // 抢占2，子优先级3
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    // 中断使能
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    // NVIC初始化
    NVIC_Init( &NVIC_InitStructure );
}

/**
  * @brief  Window Watch Dog Init
  * @param  None
  * @retval None
  */
void WWDG_Init( void )
{
    // WWDG时钟使能
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_WWDG, ENABLE );
    // 设置WWDG预分频值
    WWDG_SetPrescaler( WWDG_WINDOW_PRESCALER );
    // 设置窗口值
    WWDG_SetWindowValue( WWDG_WINDOW_VALUE );
    // 使能看门狗 ,    设置 counter
    WWDG_Enable( WWDG_WINDOW_CNT );
    // 清除提前唤醒中断标志位
    WWDG_ClearFlag();
    // 初始化窗口看门狗 NVIC
    WWDG_NVIC_Init();
    // 开启窗口看门狗中断
    WWDG_EnableIT();
}

/**
  * @brief  Window Watch Dog Feed
  * @param  None
  * @retval None
  */
void WWDG_Feed( void )
{
    WWDG_Enable( WWDG_WINDOW_CNT );
}

/**
  * @brief  WWDG_IRQHandler
  * @param  None
  * @retval None
  */
void WWDG_IRQHandler( void )
{
    WWDG_Feed();
    // 清中断标志
    WWDG_ClearFlag();
}

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
