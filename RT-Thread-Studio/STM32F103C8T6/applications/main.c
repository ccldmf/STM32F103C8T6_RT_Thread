/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-09-09     RT-Thread    first version
 */

#include <rtthread.h>
#include <board.h>
#include <rtdevice.h>
#include "./LED/led.h"
#include "./UART/uart.h"

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#define SAMPLE_UART_NAME       "uart3"    /* 串口设备名称 */

int main(void)
{
    const char str[] = "hello RT-Thread!\r\n";
    const char str2[] = "hello RT-Thread2!\r\n";
    const char str3[] = "hello RT-Thread3!\r\n";

    LED_Init();

    UART_Init(USING_UART_PORT_1);
    UART_Init(USING_UART_PORT_2);
    UART_Init(USING_UART_PORT_3);

    while (1)
    {
        LED_On();
        //LOG_D("Hello RT-Thread!!!!!!!!");
        rt_thread_mdelay(100);
        LED_Off();

        UART_SendString(USING_UART_PORT_1,str,sizeof(str));
        UART_SendString(USING_UART_PORT_2,str2,sizeof(str2));
        UART_SendString(USING_UART_PORT_3,str3,sizeof(str3));

        rt_thread_mdelay(100);
    }

    return RT_EOK;
}
