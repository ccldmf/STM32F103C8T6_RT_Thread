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
#include <string.h>
#include "uart.h"

#if defined BSP_USING_ESP8266
#include "../ESP8266/esp8266.h"
#endif

/*-----------------------------------------------------
System UART Configure Information
-----------------------------------------------------*/
#if defined BSP_USING_UART1
rt_device_t mUART_PORT_1;
#endif
#if defined BSP_USING_UART2
rt_device_t mUART_PORT_2;
#endif
#if defined BSP_USING_UART3
rt_device_t mUART_PORT_3;
#endif

rt_device_t mCurrent_UART_PORT;

/*-----------------------------------------------------
Semaphore Information
-----------------------------------------------------*/
#if defined BSP_USING_SEMAPHORE
static struct rt_semaphore mRX_Sem;
#endif

/*-----------------------------------------------------
UART Receive Callback function
-----------------------------------------------------*/
void (*mCallBackFunction)(char *);

/*-----------------------------------------------------
UART Receive Data Thread Configure
-----------------------------------------------------*/
#define UART_RECV_DATA_THREAD_NAME          "RX_THD"
#define UART_RECV_DATA_THREAD_PRIORITY      25
#define UART_RECV_DATA_THREAD_STACK_SIZE    512
#define UART_RECV_DATA_THREAD_TIMESLICE     5

/**
  * @brief  UART1 Init
  * @param  None
  * @retval None
  */
#if defined BSP_USING_UART1
static void UART1_Init(void)
{
    mUART_PORT_1 = rt_device_find("uart1");                                        /* 查找串口设备 */
    struct serial_configure theConfig = RT_SERIAL_CONFIG_DEFAULT;                  /* 配置参数 */
    rt_device_control(mUART_PORT_1,RT_DEVICE_CTRL_CONFIG,&theConfig);              /* 控制串口设备。通过控制接口传入命令控制字，与控制参数 */
    rt_device_open(mUART_PORT_1,RT_DEVICE_FLAG_INT_RX);                            /* 以中断接收及轮询发送模式打开串口设备 */
}
#endif

/**
  * @brief  UART2 Init
  * @param  None
  * @retval None
  */
#if defined BSP_USING_UART2
static void UART2_Init(void)
{
    mUART_PORT_2 = rt_device_find("uart2");                                        /* 查找串口设备 */
    struct serial_configure theConfig = RT_SERIAL_CONFIG_DEFAULT;                  /* 配置参数 */
    rt_device_control(mUART_PORT_2,RT_DEVICE_CTRL_CONFIG,&theConfig);              /* 控制串口设备。通过控制接口传入命令控制字，与控制参数 */
    rt_device_open(mUART_PORT_2,RT_DEVICE_FLAG_INT_RX);                            /* 以中断接收及轮询发送模式打开串口设备 */
}
#endif

/**
  * @brief  UART3 Init
  * @param  None
  * @retval None
  */
#if defined BSP_USING_UART3
static void UART3_Init(void)
{
    mUART_PORT_3 = rt_device_find("uart3");                                        /* 查找串口设备 */
    struct serial_configure theConfig = RT_SERIAL_CONFIG_DEFAULT;                  /* 配置参数 */
    rt_device_control(mUART_PORT_3,RT_DEVICE_CTRL_CONFIG,&theConfig);              /* 控制串口设备。通过控制接口传入命令控制字，与控制参数 */
    rt_device_open(mUART_PORT_3,RT_DEVICE_FLAG_INT_RX);                            /* 以中断接收及轮询发送模式打开串口设备 */
}
#endif

/**
  * @brief  Semaphore Init
  * @param  None
  * @retval None
  */
#if defined BSP_USING_SEMAPHORE
static void Semaphore_Init(void)
{
    rt_sem_init(&mRX_Sem, "RX_Sem", 0, RT_IPC_FLAG_FIFO);
}
#endif

/**
  * @brief  UART Receive Callback Function
  * @param  dev:UART port
  *         size:data
  * @retval
  */
static rt_err_t UART_Receive_Data(rt_device_t dev, rt_size_t size)
{
    if(size > 0)
    {
#if defined BSP_USING_SEMAPHORE
        rt_sem_release(&mRX_Sem);
#endif
    }
    return RT_EOK;
}

/**
  * @brief  UART Read a byte data
  * @param  None
  * @retval Read data
  */
static char UART_Read_One_Byte(void)
{
    char theData;
    while(rt_device_read(mCurrent_UART_PORT, 0, &theData, 1) == 0)
    {
#if defined BSP_USING_SEMAPHORE
        rt_sem_control(&mRX_Sem, RT_IPC_CMD_RESET, RT_NULL);
        rt_sem_take(&mRX_Sem, RT_WAITING_FOREVER);
#endif
    }
    return theData;
}

/**
  * @brief  UART Receive Handle Thread
  * @param  None
  * @retval None
  */
static void UART_Receive_Handle_Thread(void)
{
    char theData;
    char recv_data[RT_SERIAL_RB_BUFSZ];
    char i = 0;

    memset(recv_data, 0, RT_SERIAL_RB_BUFSZ);

    while(1)
    {
        // Read a byte
        theData = UART_Read_One_Byte();

        recv_data[i++] = theData;

        // Compare received data
        if(NULL != mCallBackFunction)
        {
            (*mCallBackFunction)(recv_data);
        }

#if defined BSP_USING_ESP8266
        if(GetEsp8266DataCheckFlag() == 0)
        {
// Balder_test -->
            UART_SendString(USING_UART_PORT_3, recv_data, NULL);
// <-- Balder_test
            SetEsp8266DataCheckFlag();
            i = 0;
            memset(recv_data, 0, RT_SERIAL_RB_BUFSZ);
        }
#endif

        if(i > RT_SERIAL_RB_BUFSZ)
        {
            i = 0;
            memset(recv_data, 0, RT_SERIAL_RB_BUFSZ);
        }
    }
}

/**
  * @brief  UART Recv Daat Thread
  * @param  None
  * @retval None
  */
static void UART_Receive_Data_Thread_Init(void)
{
    rt_thread_t theRecvDataThread;
    theRecvDataThread = rt_thread_create(UART_RECV_DATA_THREAD_NAME, (void (*)(void *parameter))UART_Receive_Handle_Thread, RT_NULL,
                                         UART_RECV_DATA_THREAD_STACK_SIZE, UART_RECV_DATA_THREAD_PRIORITY, UART_RECV_DATA_THREAD_TIMESLICE);
    if(RT_NULL == theRecvDataThread)
    {
        rt_kprintf("Receive UART Data Thread Init Error\n");
    }
    else
    {
        rt_thread_startup(theRecvDataThread);
    }
}

/**
  * @brief  Configuration UART
  * @param  aPort:UART port
  * @retval None
  */
void UART_Init(enum UART_PORT aPort)
{
    static char theFirstInit = 0;
#if defined BSP_USING_UART1
    if(USING_UART_PORT_1 == aPort)
    {
        UART1_Init();
    }
#endif
#if defined BSP_USING_UART2
    else if(USING_UART_PORT_2 == aPort)
    {
        UART2_Init();
    }
#endif
#if defined BSP_USING_UART3
    else if(USING_UART_PORT_3 == aPort)
    {
        UART3_Init();
    }
#endif
    if(0 == theFirstInit)
    {
        theFirstInit = 1;
#if defined BSP_USING_SEMAPHORE
        Semaphore_Init();
#endif
        UART_Receive_Data_Thread_Init();
        mCallBackFunction = NULL;
    }
}

/**
  * @brief  Configuration UART
  * @param  aPort:UART port
  *         aData:data
  * @retval None
  */
void UART_SendString(enum UART_PORT aPort,const char *aData, void *aCallBackFunction)
{
#if defined BSP_USING_UART1
    if(USING_UART_PORT_1 == aPort)
    {
        // Set the receive callback function
        if(NULL != aCallBackFunction)
        {
            rt_device_set_rx_indicate(mUART_PORT_1, UART_Receive_Data);
            mCallBackFunction  = aCallBackFunction;
            mCurrent_UART_PORT = mUART_PORT_1;
        }
        rt_device_write(mUART_PORT_1, 0, aData, strlen(aData));
    }
#endif
#if defined BSP_USING_UART2
    else if(USING_UART_PORT_2 == aPort)
    {
        // Set the receive callback function
        if(NULL != aCallBackFunction)
        {
            rt_device_set_rx_indicate(mUART_PORT_2, UART_Receive_Data);
            mCallBackFunction  = aCallBackFunction;
            mCurrent_UART_PORT = mUART_PORT_2;
        }
        rt_device_write(mUART_PORT_2, 0, aData, strlen(aData));
    }
#endif
#if defined BSP_USING_UART3
    else if(USING_UART_PORT_3 == aPort)
    {
        // Set the receive callback function
        if(NULL != aCallBackFunction)
        {
            rt_device_set_rx_indicate(mUART_PORT_3, UART_Receive_Data);
            mCallBackFunction  = aCallBackFunction;
            mCurrent_UART_PORT = mUART_PORT_3;
        }
        rt_device_write(mUART_PORT_3, 0, aData, strlen(aData));
    }
#endif
}

