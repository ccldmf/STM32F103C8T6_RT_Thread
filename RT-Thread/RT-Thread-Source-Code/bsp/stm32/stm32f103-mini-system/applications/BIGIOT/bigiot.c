/**
 * @brief
 * @file     bigito.c
 * @author   cc
 * @version
 * @date     Wed 27 Jun 2018 01:30:42 AM PDT
 * @mail     13568859409@163.com
 * @note
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bigiot.h"

#include "../ESP8266/esp8266.h"

static char mBigiotLoginSuccessfulFlag = 0;

/**
 *@brief  设备登录成功标志
 *@param  None
 *@return 1:成功  0:失败
 */
char BigiotLoginSuccessfulFlag(void)
{
    return mBigiotLoginSuccessfulFlag;
}

/**
 *@brief  设备登录返回结果
 *@param  recv_data:收到的返回数据
 *@return 无
 */
static void BigiotLoginCallbackFunc(char *recv_data)
{
    // Return Data:{"M":"checkinok","ID":"xx1","NAME":"xx2","T":"xx3"}\n
    if(NULL != strstr(recv_data, "checkinok"))
    {
        mBigiotLoginSuccessfulFlag = 1;
    }
}

/**
 *@brief  设备登录
 *@param  id:设备ID apikey:设备apikey
 *@return 无
 */
void BigiotLogin(const char *id,const char *apikey)
{
    mBigiotLoginSuccessfulFlag = 0;
    char theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"checkin\",\"ID\":\"%s\",\"K\":\"%s\"}\n", id, apikey);
    Esp8266SendData(theSendPtr, BigiotLoginCallbackFunc);
}

/**
 *@brief  发送数据
 *@param  id:设备id data_id:数据接口ID value:值
 *@return 无
 */
void BigiotSendSingleData(const char *id,const char *data_id,char value)
{
    char theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"update\",\"ID\":\"%s\",\"V\":{\"%s\":\"%d\"}}\n", id, data_id, value);
    Esp8266SendData(theSendPtr, NULL);
}

/**
 *@brief  查询设备是否在线结果
 *@param  recv_data：接收到数据
 *@return 无
 */
static void BigiotIsOnLineCallbackFunc(char *recv_data)
{
    // Return data: {"M":"isOL","R":{"XX1":"xx1",...},"T"":"xx3"}\n
    if(NULL != strstr(recv_data, ":\"1"))
    {
        rt_kprintf("BigiotIsOnLineCallbackFunc OK\n");
    }
    else
    {
        rt_kprintf("BigiotIsOnLineCallbackFunc Fail\n");
    }
}

/**
 *@brief  查询设备是否在线
 *@param  id:设备的id
 *@return 无
 */
void BigiotIsOnLine(const char *id)
{
    char theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"isOL\",\"ID\":[\"D%s\"]}\n", id);
    rt_kprintf("BigiotIsOnLine send data:%s\n", theSendPtr);
    Esp8266SendData(theSendPtr, BigiotIsOnLineCallbackFunc);
}

/**
 *@brief  设备下线结果
 *@param  recv_data：Recv Data
 *@return 无
 */
static void BigiotLogoutCallbackFunc(char *recv_data)
{
    rt_kprintf("BigiotLogoutCallbackFunc data:%s\n",recv_data);
    if(NULL != strstr(recv_data, "checkout"))
    {
        rt_kprintf("BigiotLogoutCallbackFunc OK\n");
    }
}

/**
 *@brief  设备下线
 *@param  id:设备id  apikey:设备apikey
 *@return 无
 */
void BigiotLogout(const char *id,const char *apikey)
{
    char theSendPtr[60] = {0};
    sprintf(theSendPtr,"{\"M\":\"checkout\",\"ID\":\"%s\",\"K\":\"%s\"}\n", id, apikey);
    Esp8266SendData(theSendPtr, BigiotLogoutCallbackFunc);
}

