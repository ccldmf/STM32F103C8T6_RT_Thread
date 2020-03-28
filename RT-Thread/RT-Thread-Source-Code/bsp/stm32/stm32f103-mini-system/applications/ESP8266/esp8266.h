/**
 * @brief
 * @file     esp8266.h
 * @author   cc
 * @version
 * @date     Sat 30 Jun 2018 11:17:55 PM PDT
 * @mail     13568859409@163.com
 * @note
 */

#ifndef _ESP8266_H
#define _ESP8266_H

/**
 *@brief  Esp8266数据检查
 *@return 成功：0 失败：-1
 */
char GetEsp8266DataCheckFlag(void);

/**
 *@brief  Esp8266数据检查设置
 *@return None
 */
void SetEsp8266DataCheckFlag(void);

/**
 *@brief Esp8266模块检测
 *@param None
 */
void Esp8266Check(void);

/**
 *@brief  Esp8266模块硬件重启
 *@return None
 */
void Esp8266HartReseat(void);

/**
 *@brief  Esp8266模块重启
 *@return None
 */
void Esp8266Reseat(void);

/**
 *@brief  Esp8266恢复出厂设置
 *@return None
 */
void Esp8266ResetFactoryData(void);

/**
 *@brief  Esp8266模块STA应用模式
 *@param  None
 *@return None
 */
void Esp8266SetSTAMode(void);

/**
 *@brief  Esp8266模块设置路由器
 *@param  ssid:路由器名 password:密码
 *@return None
 */
void Esp8266SetRouter(const char *ssid,const char *password);

/**
 *@brief  Esp8266查看连接路由器
 *@return None
 */
void Esp8266CheckConnectRouter(void);

/**
 *@brief  Esp8266模块IP获取
 *@param  None
 *@return None
 */
void Esp8266GetLocalIPAddr(void);

/**
 *@brief  Esp8266模块连接到服务器
 *@param  type:通信协议类型 ip:服务器ip地址 port服务器端口
 *@return None
 */
void Esp8266ConnectServer(const char *type,const char *ip,const unsigned int port);

/**
 *@brief  Esp8266模块设置开启透传模式
 *@param  None
 *@return None
 */
void Esp8266SetTransMode(void);

/**
 *@brief  Esp8266模块开始透传
 *@param  None
 *@return None
 */
void Esp8266StartTransmission(void);

/**
 *@brief  Esp8266退出透传模式
 *@param  None
 *@return None
 */
void Esp8266QuitTransmission(void);

/**
 *@brief  Esp8266退出与路由器的AP连接
 *@return None
 */
void Esp8266QuitRouterAPConnect(void);

/**
 *@brief  Esp8266设置STA开机自动连接
 *@param  en:使能控制
 *@return None
 */
void Esp8266SetSTAAutoConnect(unsigned char en);

/**
 *@brief  Esp8266断开TCP或者UDP连接
 *@param  None
 *@return None
 */
void Esp8266DisableConnect(void);

/*****************************************************/
/**
 *@brief Esp8266模块初始化
 *@param None
 */
void Esp8266Init(void);

/**
 *@brief Esp8266设置连接到WiFi参数
 *@param ssid: WiFi名  password: WiFi密码  aCallback:设置参数成功与否的回调函数
 *@return None
 */
void Esp8266SetRouterParameter(const char *ssid,const char *password, void *aCallback);

/**
 *@brief  Esp8266模块连接到服务器参数
 *@param  type:通信协议类型 ip:服务器ip地址 port服务器端口 aCallback:设置参数成功与否的回调函数
 *@return None
 */
void Esp8266ConnectServerParameter(const char *type,const char *ip,const unsigned int port, void *aCallback);

/**
 *@brief  Esp8266模块发送数据
 *@param  data:发送的数据字符串,此时不需要添加回车
 *@param  aCallback:如果需要响应，则该函数为响应数据函数
 *@return None
 */
void Esp8266SendData(const char *data, void *aCallback);

#endif  /* _ESP8266_H */

