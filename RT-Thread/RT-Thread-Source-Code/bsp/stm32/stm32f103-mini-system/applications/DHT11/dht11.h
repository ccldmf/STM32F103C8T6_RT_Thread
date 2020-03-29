/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2019-08-01     LuoGong         the first version.
 * 2019-08-15     MurphyZhao      add lock and modify code style
 *
 */

#ifndef __DHT11_H__
#define __DHT11_H__

#include <rtthread.h>
#include <sensor.h>

/**
 *@brief  DHT11模块初始化
 *@param  None
 *@return 1:成功  0:失败
 */
int DHT11_Init(void);

/**
 *@brief  DHT11模块温度湿度数据读取
 *@param  None
 *@return 温度和湿度数据
 */
rt_int32_t DHT11_GetTempAndHumi(void);


#endif /* __DHT11_H__ */


