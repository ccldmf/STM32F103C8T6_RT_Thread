/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-08     obito0   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "./UART/uart.h"
#include "./ESP8266/esp8266.h"
#include "./BIGIOT/bigiot.h"
#include "./DHT11/dht11.h"



int main(void)
{
    int ret;
    int i = 0;
    uint8_t theTemp,theHumi;
    rt_int32_t theTempAndHumi;
    rt_thread_mdelay(2000);         // Wait the ESP8266 module to work normally
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);
    UART_Init(USING_UART_PORT_2);
    UART_Init(USING_UART_PORT_3);
    Esp8266Init();
    ret = DHT11_Init();
    if(0 != ret)
    {
        rt_kprintf("DHT11_Init failure\n");
        return RT_ERROR;
    }

    while(1)
    {
        rt_pin_write(LED0_PIN, 0);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, 1);
        rt_thread_mdelay(500);

        if( 1 == BigiotLoginSuccessfulFlag() )
        {
            theTempAndHumi = DHT11_GetTempAndHumi();
            theTemp = (theTempAndHumi & 0xffff) >> 0;
            theHumi = (theTempAndHumi & 0xffff0000) >> 16;
            //rt_kprintf("Temp:%d,  Humi:%d\n",theTemp, theHumi);
            if(i%2 == 0)
            {
                BigiotSendSingleData(BIGIOT_SMART_HOUSE_ID,BIGIOT_SMART_HOUSE_TEMPERATURE, theTemp);
            }
            else
            {
                BigiotSendSingleData(BIGIOT_SMART_HOUSE_ID,BIGIOT_SMART_HOUSE_HUMIDITY, theHumi);
            }
            i++;
            rt_thread_mdelay(5000);
        }
    }

    return RT_EOK;
}
