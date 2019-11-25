/**
  ******************************************************************************
  * @file    Modules/DHT11/dht11.c
  * @author  CC
  * @version V1.0.0
  * @date    25-11-2019
  * @brief   DHT11 module driver.
  *          This file provides control the DHT11 module.
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "dht11.h"
#include "delay.h"

/* Define a global parameter to save the data of read from DHT11 module. -----*/
DHT11_TypeDef DHT11;

/* Define function -----------------------------------------------------------*/
#define DHT11_SetBit()    GPIO_SetBits( DHT11_GPIO , DHT11_GPIO_PIN )
#define DHT11_ResetBit()  GPIO_ResetBits( DHT11_GPIO , DHT11_GPIO_PIN )
#define DHT11_ReadBit()   GPIO_ReadInputDataBit( DHT11_GPIO , DHT11_GPIO_PIN )

static void DHT11_Set_Output( void )
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( DHT11_RCC , ENABLE );
    GPIO_InitStructure.GPIO_Pin   = DHT11_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( DHT11_GPIO , &GPIO_InitStructure );
}

static void DHT11_Set_Input( void )
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd( DHT11_RCC , ENABLE );
    GPIO_InitStructure.GPIO_Pin   = DHT11_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( DHT11_GPIO , &GPIO_InitStructure );
}

static uint32_t DHT11_ReadByte( void )
{
    uint32_t theData=0;
    char i;
    char theCout;

    DHT11_Set_Input();

    for( i = 0 ; i < 8 ; i++ )
    {
        // Read the low level of 50us
        theCout = 1;
        while( !DHT11_ReadBit() && theCout++ );

        // Read the status of IO port after a delay of 30us
        Delay_us( 30 );

        // Shift the last data first, and then save the data bit this time
        theData = theData << 1;
        if( DHT11_ReadBit() == Bit_SET )
        {
            theData |= 1;
        }

        // Waiting for input is low level, enter the next bit of data to receive
        theCout = 1;
        while( DHT11_ReadBit() && theCout++ );
    }
    return theData;
}

/**
  * @brief  DHT11 Init
  * @param  None
  * @retval None
  */
void DHT11_Init( void )
{
    DHT11_Set_Output();
    DHT11.Tem_H = 0;
    DHT11.Tem_L = 0;
    DHT11.Hum_H = 0;
    DHT11.Hum_L = 0;
}

/**
  * @brief  Read DHT11 data
  * @param  None
  * @retval None
  */
uint32_t DHT11_ReadData( void )
{
    uint32_t theCout = 1;
    uint32_t T_H, T_L, H_H, H_L, theCheck;

    //设置为IO口输出模式
    DHT11_Set_Output();

    //1、MCU开始起始信号
    DHT11_ResetBit();
    Delay_ms(20);       //拉低至少18ms
    DHT11_SetBit();
    Delay_us(30);       //拉高20~40us

    //设置为IO口输入模式
    DHT11_Set_Input();

    //2、读取DH21响应
    if( DHT11_ReadBit() == Bit_RESET )
    {
        //等待80us的低电平
        theCout = 1;
        while( !DHT11_ReadBit() && theCout++ );

        //等待80us的高电平
        theCout = 1;
        while( DHT11_ReadBit() && theCout++ );

        //读取8bit的湿度整数数据
        H_H = DHT11_ReadByte();

        //读取8bit的湿度小数数据
        H_L = DHT11_ReadByte();

        //读取8bit的温度整数数据
        T_H = DHT11_ReadByte();

        //读取8bit的温度小数数据
        T_L = DHT11_ReadByte();

        //读取8bit的校验和
        theCheck = DHT11_ReadByte();

        if( theCheck == ( H_H + H_L + T_H + T_L ) )
        {
            DHT11.Hum_H = H_H;
            DHT11.Hum_L = H_L;
            DHT11.Tem_H = T_H;
            DHT11.Tem_L = T_L;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;

}

/**
  * @brief  Get DHT11 temperature
  * @param  None
  * @retval None
  */
float DHT11_GetTem( void )
{
    return (DHT11.Tem_H << 8 | DHT11.Tem_L);
}

/**
  * @brief  Get DHT11 humidity
  * @param  None
  * @retval None
  */
float DHT11_GetHum( void )
{
    return (DHT11.Hum_H << 8 | DHT11.Hum_L);
}

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
