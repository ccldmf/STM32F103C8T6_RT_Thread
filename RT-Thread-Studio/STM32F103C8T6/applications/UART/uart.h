/**
  ******************************************************************************
  * @file    applications/UART/uart.h
  * @author  CC
  * @version V1.0.0
  * @date    02-05-2020
  * @brief   This file contains the headers of the UART handlers.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
 extern "C" {
#endif

 /* Includes ------------------------------------------------------------------*/
 #include <rtthread.h>
 #include <board.h>
 #include <rtdevice.h>

 enum UART_PORT
 {
 #if defined(BSP_USING_UART1)
     USING_UART_PORT_1,
 #endif
 #if defined(BSP_USING_UART2)
     USING_UART_PORT_2,
 #endif
 #if defined(BSP_USING_UART3)
     USING_UART_PORT_3,
 #endif
 #if defined(BSP_USING_UART4)
     USING_UART_PORT_4,
 #endif
 #if defined(BSP_USING_UART5)
     USING_UART_PORT_5,
 #endif
 #if defined(BSP_USING_UART6)
     USING_UART_PORT_6,
 #endif
 #if defined(BSP_USING_UART7)
     USING_UART_PORT_7,
 #endif
 #if defined(BSP_USING_UART7)
     USING_UART_PORT_8,
 #endif
 };

void UART_Init(enum UART_PORT);

void UART_SendString(enum UART_PORT, const char *,int);

#ifdef __cplusplus
}
#endif

#endif /* __UART_H */
/******************* (C) COPYRIGHT 2020 CC *****END OF FILE****/
