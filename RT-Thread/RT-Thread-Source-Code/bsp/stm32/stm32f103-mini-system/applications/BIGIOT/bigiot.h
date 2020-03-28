/**
 * @brief
 * @file     bigiot.h
 * @author   cc
 * @version
 * @date     Wed 27 Jun 2018 01:02:14 AM PDT
 * @mail     13568859409@163.com
 * @note
 */

#ifndef _BIGIOT_H
#define _BIGIOT_H

/**
 *@brief 设备登录
 *@param id:设备ID apikey:设备apikey
 *@return 无
 */
void BigiotLogin(const char *id,const char *apikey);

/**
 *@brief 发送数据
 *@param id:设备id data_id:数据接口ID value:值
 *@return 无
 */
void BigiotSendSingleData(const char *id,const char *data_id,const char *value);

/**
 *@brief 查询设备是否在线
 *@param id:设备的id
 *@return 无
 */
void BigiotIsOnLine(const char *id);

/**
 *@brief 设备下线
 *@param id:设备id  apikey:设备apikey
 *@return 无
 */
void BigiotLogout(const char *,const char *);

#endif
