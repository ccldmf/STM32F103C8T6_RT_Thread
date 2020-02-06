/**
  ******************************************************************************
  * @file    applications/Usart/usart.c
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
#include "uart.h"
#include <string.h>

rt_device_t mUART_PORT_1;
rt_device_t mUART_PORT_2;
rt_device_t mUART_PORT_3;

/**
  * @brief  UART1 Init
  * @param  None
  * @retval None
  */
static void UART1_Init(void)
{
    mUART_PORT_1 = rt_device_find("uart1");                                        /* 查找串口设备 */
    struct serial_configure theConfig = RT_SERIAL_CONFIG_DEFAULT;                  /* 配置参数 */
    rt_device_control(mUART_PORT_1,RT_DEVICE_CTRL_CONFIG,&theConfig);              /* 控制串口设备。通过控制接口传入命令控制字，与控制参数 */
    rt_device_open(mUART_PORT_1,RT_DEVICE_FLAG_INT_RX);                            /* 以中断接收及轮询发送模式打开串口设备 */
}

/**
  * @brief  UART2 Init
  * @param  None
  * @retval None
  */
static void UART2_Init(void)
{
    mUART_PORT_2 = rt_device_find("uart2");                                        /* 查找串口设备 */
    struct serial_configure theConfig = RT_SERIAL_CONFIG_DEFAULT;                  /* 配置参数 */
    rt_device_control(mUART_PORT_2,RT_DEVICE_CTRL_CONFIG,&theConfig);              /* 控制串口设备。通过控制接口传入命令控制字，与控制参数 */
    rt_device_open(mUART_PORT_2,RT_DEVICE_FLAG_INT_RX);                            /* 以中断接收及轮询发送模式打开串口设备 */
}

/**
  * @brief  UART3 Init
  * @param  None
  * @retval None
  */
static void UART3_Init(void)
{
    mUART_PORT_3 = rt_device_find("uart3");                                        /* 查找串口设备 */
    struct serial_configure theConfig = RT_SERIAL_CONFIG_DEFAULT;                  /* 配置参数 */
    rt_device_control(mUART_PORT_3,RT_DEVICE_CTRL_CONFIG,&theConfig);              /* 控制串口设备。通过控制接口传入命令控制字，与控制参数 */
    rt_device_open(mUART_PORT_3,RT_DEVICE_FLAG_INT_RX);                            /* 以中断接收及轮询发送模式打开串口设备 */
}

/**
  * @brief  Configuration UART
  * @param  aPort:UART port
  * @retval None
  */
void UART_Init(enum UART_PORT aPort)
{
    if(USING_UART_PORT_1 == aPort)
    {
        UART1_Init();
    }
    else if(USING_UART_PORT_2 == aPort)
    {
        UART2_Init();
    }
    else if(USING_UART_PORT_3 == aPort)
    {
        UART3_Init();
    }
}

/**
  * @brief  Configuration UART
  * @param  aPort:UART port
  *         aData:data
  * @retval None
  */
void UART_SendString(enum UART_PORT aPort,const char *aData)
{
    if(USING_UART_PORT_1 == aPort)
        {
            rt_device_write(mUART_PORT_1,0,aData,strlen(aData));
        }
        else if(USING_UART_PORT_2 == aPort)
        {
            rt_device_write(mUART_PORT_2,0,aData,strlen(aData));
        }
        else if(USING_UART_PORT_3 == aPort)
        {
            rt_device_write(mUART_PORT_3,0,aData,strlen(aData));
        }
}
