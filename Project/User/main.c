/**
  ******************************************************************************
  * @file    User/main.c
  * @author  CC
  * @version V1.0.0
  * @date    02-11-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "esp8266.h"
#include "bigiot.h"
#include "dht11.h"
#include <stdio.h>
#include "systemConfigure.h"
#ifdef ENABLE_LCD_MODULE
#include "lcd.h"
#include "systemColor.h"
#endif
#ifdef ENABLE_RC522_MODULE
#include "rc522.h"
#endif

#ifdef ENABLE_RC522_MODULE
static uint8_t WriteAmount( uint8_t aAddr , uint32_t aValue )
{
    uint8_t theStatus;
    uint8_t theComBuf[ 16 ];

    theComBuf[0] = (aValue&((uint32_t)0x000000ff));
    theComBuf[1] = (aValue&((uint32_t)0x0000ff00))>>8;
    theComBuf[2] = (aValue&((uint32_t)0x00ff0000))>>16;
    theComBuf[3] = (aValue&((uint32_t)0xff000000))>>24;

    theComBuf[4] = ~(aValue&((uint32_t)0x000000ff));
    theComBuf[5] = ~(aValue&((uint32_t)0x0000ff00))>>8;
    theComBuf[6] = ~(aValue&((uint32_t)0x00ff0000))>>16;
    theComBuf[7] = ~(aValue&((uint32_t)0xff000000))>>24;

    theComBuf[8] = (aValue&((uint32_t)0x000000ff));
    theComBuf[9] = (aValue&((uint32_t)0x0000ff00))>>8;
    theComBuf[10] = (aValue&((uint32_t)0x00ff0000))>>16;
    theComBuf[11] = (aValue&((uint32_t)0xff000000))>>24;

    theComBuf[12] = aAddr;
    theComBuf[13] = ~aAddr;
    theComBuf[14] = aAddr;
    theComBuf[15] = ~aAddr;

    theStatus = RC522_WriteDataToBlock( aAddr, theComBuf );
    return theStatus;
}

static uint8_t ReadAmount( uint8_t aAddr , uint32_t *aData )
{
    uint8_t theStatus = MI_ERR;
    uint8_t i , theComBuf[ 16 ];

    theStatus = RC522_ReadDataFromBlock( aAddr , theComBuf );
    if( theStatus != MI_OK )
    {
        return theStatus;
    }

    for( i = 0 ; i < 4 ; i++ )
    {
        if( ( theComBuf[ i ] != theComBuf[ i + 8 ] ) && ( theComBuf[ i ] != ~theComBuf[ i + 8 ] ) )
        {
            break;
        }
    }
    if( i == 4 )
    {
        theStatus = MI_OK;
        *aData = theComBuf[ 0 ] + ( theComBuf[ 1 ] << 8 ) + ( theComBuf[ 2 ] << 16 ) + ( theComBuf[ 3 ] << 24 );
    }
    else
    {
        theStatus = MI_ERR;
        *aData = 0;
    }
    return theStatus;
}


uint8_t KeyValue[]={0xFF ,0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
void IC_test ( void )
{
    uint32_t writeValue = 100;
    uint32_t readValue;
    char cStr [ 30 ];
    uint8_t ucArray_ID [ 4 ];
    uint8_t ucStatusReturn;
    if ( ( ucStatusReturn = RC522_LookForCard( PICC_REQIDL, ucArray_ID ) ) != MI_OK )
    ucStatusReturn = RC522_LookForCard( PICC_REQIDL, ucArray_ID );

    if ( ucStatusReturn == MI_OK )
    {
        if ( RC522_PreventCollision( ucArray_ID ) == MI_OK )
        {
            RC522_SelectCard(ucArray_ID);

            RC522_VerifyCardPassword( PICC_AUTHENT1A, 0x11, KeyValue, ucArray_ID );
            WriteAmount(0x11,writeValue);
            if(ReadAmount(0x11,&readValue) == MI_OK)
            {
                writeValue +=100;
                sprintf ( cStr, "The Card ID is: %02X%02X%02X%02X",ucArray_ID [0], ucArray_ID [1], ucArray_ID [2],ucArray_ID [3] );
                printf ( "%s\r\n",cStr );


                printf ("The balance is:%d\r\n",readValue);
                sprintf ( cStr, "TThe residual amount: %d", readValue);
                RC522_SetCardToDormancyState();
            }
        }
    }
}
#endif /* ENABLE_RC522_MODULE */

#ifdef ENABLE_LCD_MODULE
static void LCD_Test(void)
{
    int i,j;
    for( i = 0; i < LCD_WIDTH; i++ )
    {
        for( j = 0; j < LCD_HEIGHT; j++ )
        {
            Lcd_DrawPoint( i , j , YELLOW );
        }
    }

    Lcd_SetColor( RED );
    Delay_ms(500);
    Lcd_SetColor(GRAY0);
    Delay_ms(500);
}
#endif

/**
  * @brief  Application.
  * @param  None
  * @retval None
  */
int main(void)
{
    //uint32_t theHighValue,theLowValue;
    //uint32_t theTmp;
    SystemInit();
    LED_Init();
    Delay_Init();
    USART_Configuration(USART1,115200);
    USART_Configuration(USART2,115200);
    USART_Configuration(USART3,115200);
    //DHT11_Init();
#ifdef ENABLE_RC522_MODULE
    RC522_Init ();
    RC522_Reset();
    RC522_ConfigType( 'A' );
#endif
#ifdef ENABLE_LCD_MODULE
    Lcd_Init();
    Lcd_BLK_Turn_On();
#endif
    printf("************************************\n");
    printf("*          Smart House Iinit       *\n");
    printf("************************************\n");

    while(1)
    {
    #ifdef ENABLE_RC522_MODULE
        IC_test ();
    #endif
    #ifdef ENABLE_LCD_MODULE
        LCD_Test();
    #endif
    LED_On();
    Delay_ms(500);
    LED_Off();
    Delay_ms(500);
    /*
    DHT11_ReadData();
    theTmp = DHT11_GetTem();
    printf("Tem = %d.%d\n" , (theTmp>>8) , (theTmp&0xFF));
    theTmp = DHT11_GetHum();
    printf("Hum = %d.%d\n" , (theTmp>>8) , (theTmp&0xFF));
    */
    }
}

