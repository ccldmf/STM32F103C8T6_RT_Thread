/**
  ******************************************************************************
  * @file    Sample/SampleTest.h
  * @author  CC
  * @version V1.0.0
  * @date    08-23-2020
  * @brief   This file provider the system module test.
  *
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#include "stm32f10x.h"
#include "systemConfigure.h"
#include "delay.h"

#ifdef ENABLE_DHT11_MODULE
#include "dht11.h"
#endif
#ifdef ENABLE_RC522_MODULE
#include "rc522.h"
#endif
#ifdef ENABLE_LCD_MODULE
#include "lcd.h"
#include "systemColor.h"
#ifdef USING_GUI
#include "GUI.h"
#include "Picture.h"
#endif
#endif

#ifdef ENABLE_TEST_MODULE

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

#ifdef USING_GUI
void Num_Test( void )
{
	unsigned char Num[ 10 ] = { 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 };
    u8 i = 0;
    Lcd_SetColor( GRAY0 );
    Gui_DrawFont_GBK16( 16 , 20 , RED , GRAY0 , "Num Test" );
    Delay_ms( 1000 );
    Lcd_SetColor( GRAY0 );

    for( i = 0 ; i < 10 ; i++ )
    {
        GUI_DrawNum( ( i % 3 ) * 40 , 32 * ( i / 3 ) + 5 , RED , GRAY0 , Num[ i + 1 ] );
        Delay_ms( 100 );
    }
}

static void GUI_Test( void )
{
	Gui_Circle( 30 , 30 , 20 , RED );
	Gui_DrawLine( 10 , 24 , 100 , 150 , BLUE );
	GUI_DrawButtonUp( 15 , 68 , 113 , 88 );
	GUI_DrawButtonDown( 15 , 100 , 113 , 120 );
	Delay_ms( 2000 );
	GUI_DrawImage( 120 , 90 , mImage );
	Delay_ms( 3000 );
	Num_Test();
	Delay_ms( 3000 );
}
#endif


#ifdef ENABLE_DHT11_MODULE
static void DHT11_ShowInfo( void )
{
	uint32_t theTmp , theHum;
#ifdef USING_GUI
	uint32_t thePositionX , thePositionY;
	uint16_t theFontColor , theBackgoundColor;
#endif
	
    DHT11_ReadData();
    theTmp = DHT11_GetTem();
	theHum = DHT11_GetHum();
	theTmp = ( theTmp >> 8 );
	theHum = ( theHum >> 8 );
#ifdef USING_GUI
	thePositionX = 10;
	thePositionY = 20;
	theFontColor = BLUE;
	theBackgoundColor = WHITE;
	Lcd_SetColor( WHITE );
	Gui_DrawFont_GBK16( thePositionX , thePositionY , theFontColor , theBackgoundColor , "Temperature:" );
	GUI_DisplayNumber( thePositionX + 12 * 8 , thePositionY , theFontColor , theBackgoundColor , theTmp );

	thePositionY += 20;
	Gui_DrawFont_GBK16( thePositionX , thePositionY , theFontColor , theBackgoundColor , "Humidity:" );
	GUI_DisplayNumber( thePositionX + 9 * 8 , thePositionY , theFontColor , theBackgoundColor , theHum );
#else
    printf("Tem = %d\n" , theTmp );
    printf("Hum = %d\n" , theHum );
#endif

}
#endif


void SampleTest( void )
{
#ifdef ENABLE_RC522_MODULE
	IC_test ();
#endif

#if 0
#ifdef ENABLE_LCD_MODULE
	LCD_Test();
#endif
	
#ifdef USING_GUI
	GUI_Test();
#endif
#endif

#ifdef ENABLE_DHT11_MODULE
	DHT11_ShowInfo();
#endif
}

#endif /* ENABLE_TEST_MODULE */

