/**
  ******************************************************************************
  * @file    Modules/RC522/rc522.c
  * @author  CC
  * @version V1.0.0
  * @date    06-19-2020
  * @brief   This file provider the feature of RC522 module.
  *
  ******************************************************************************
  * @attention
  *
  * NULL
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rc522.h"
#include "systemConfigure.h"
#include "spi.h"
#include "delay.h"

#define MAXRLEN  18

/**
  * @brief  Write data to register
  * @param  aAddr: Register add
  * @param  aValue: Write data
  * @retval None
  */
static void RC522_WriteDataToRegister( uint8_t aAddr , uint8_t aValue );

/**
  * @brief  Read data from register
  * @param  aAddr: Register addr
  * @retval Read data
  */
static uint8_t RC522_ReadDataFromRegister( uint8_t aAddr );

/**
  * @brief  Clear register bit mask
  * @param  aAddr: Register addr
  * @param  aMask: Mask value
  * @retval None
  */
static void RC522_ClearBitMask( uint8_t aAddr , uint8_t aMask );

/**
  * @brief  Set register bit mask
  * @param  aAddr: Register addr
  * @param  aMask: Mask value
  * @retval None
  */
static void RC522_SetBitMask( uint8_t aAddr , uint8_t aMask );

/**
  * @brief  Open the module antenna
  * @param  None
  * @retval None
  */
static void RC522_OpenAntenna( void );

/**
  * @brief  Close the module antenna
  * @param  None
  * @retval None
  */
static void RC522_CloseAntenna( void );

/**
  * @brief  RC522 communication with card
  * @param  aCommand: communication command
  * @param  aSendData: send data buffer
  * @param  aSendDataLength: send data length
  * @param  aReceiveData: receive data buffer
  * @param  aReceiveDataLength: receive data length
  * @retval None
  */
static uint8_t RC522_CommunicationOfCard( uint8_t aCommand ,
                                          uint8_t *aSendData ,
                                          uint8_t aSendDataLength ,
                                          uint8_t *aReceiveData ,
                                          uint32_t *aReceiveDataLength );

/**
  * @brief  Calulate CRC
  * @param  aInData: calulate input data
  * @param  aInDataLength: calulate input data length
  * @param  aOutputData: calulate output data
  * @retval None
  */
static void RC522_CalulateCRC( uint8_t *aInData ,
                         uint8_t aInDataLength ,
                         uint8_t *aOutputData );

/**
  * @brief  Configure RC522 module CS pin
  * @param  None
  * @retval None
  */
static void RC522_CS_Configure( void );

/**
  * @brief  Configure RC522 module RST pin
  * @param  None
  * @retval None
  */
static void RC522_RST_Configure( void );

/**
  * @brief  RC522 module init
  * @param  None
  * @retval None
  */
void RC522_Init( void )
{
    SPIx_Init( RC522_USING_SPI );
    RC522_CS_Configure();
    RC522_RST_Configure();
    RC522_Reset_Disable();
    RC522_CS_Disable();
}

/**
  * @brief  RC522 module reset
  * @param  None
  * @retval None
  */
void RC522_Reset( void )
{
    RC522_Reset_Disable();
    Delay_us( 1 );

    RC522_Reset_Enable();
    Delay_us( 1 );

    RC522_Reset_Disable();
    Delay_us( 1 );

    RC522_WriteDataToRegister( CommandReg , 0x0f );

    while( RC522_ReadDataFromRegister( CommandReg ) & 0x10 );

    Delay_us( 1 );

    RC522_WriteDataToRegister( ModeReg , 0x3D );            // Define the comman mode of send and receive
    RC522_WriteDataToRegister( TReloadRegL , 30 );          // 16-bit tiemr low
    RC522_WriteDataToRegister( TReloadRegH , 0 );           // 16-bit time high
    RC522_WriteDataToRegister( TModeReg , 0x8D );           // Set internal timer
    RC522_WriteDataToRegister( TPrescalerReg , 0x3E );      // Set the timer frequency division factor
    RC522_WriteDataToRegister( TxAutoReg , 0x40 );          // Modulation the send signal to 100% ASK
}

/**
  * @brief  Set RC522 module work type
  * @param  aType: work type
  * @retval None
  */
void RC522_ConfigType( uint8_t aType )
{
    if( 'A' == aType )                                          // ISO14443_A
    {
        RC522_ClearBitMask( Status2Reg , 0x08 );
        RC522_WriteDataToRegister( ModeReg , 0x3D );            //3F
        RC522_WriteDataToRegister( RxSelReg , 0x86 );           //84
        RC522_WriteDataToRegister( RFCfgReg , 0x7F );           //4F
        RC522_WriteDataToRegister( TReloadRegL , 30 );
        RC522_WriteDataToRegister( TReloadRegH , 0 );
        RC522_WriteDataToRegister( TModeReg , 0x8D );
        RC522_WriteDataToRegister( TPrescalerReg , 0x3E );
        Delay_us ( 2 );
        RC522_OpenAntenna();
    }
}

/**
  * @brief  Looking for card
  * @param  aRequstCode, if aRequstCode == 0x52,look for all cards that meet 14443A standard.
  *                      if aRequstCode == 0x26,look for all cards that are not dormant.
  * @param  aCardType
  *              = 0x4400, Mifare_UltraLight
  *              = 0x0400, Mifare_One(S50)
  *              = 0x0200, Mifare_One(S70)
  *              = 0x0800, Mifare_Pro(X)
  *              = 0x4403, Mifare_DESFire
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_LookForCard( uint8_t aRequstCode , uint8_t *aCardType )
{
    uint32_t aReceiveDataLength;
    uint8_t theStatus;
    uint8_t theComRC522Buf[ MAXRLEN ];
    RC522_ClearBitMask( Status2Reg , 0x08 );
    RC522_WriteDataToRegister( BitFramingReg , 0x07 );
    RC522_SetBitMask( TxControlReg , 0x03 );

    theComRC522Buf[ 0 ] = aRequstCode;
    theStatus = RC522_CommunicationOfCard( PCD_TRANSCEIVE ,
                                           theComRC522Buf ,
                                           1 ,
                                           theComRC522Buf ,
                                           &aReceiveDataLength );
    if( ( theStatus == MI_OK ) && ( aReceiveDataLength == 0x10) )
    {
        *aCardType = theComRC522Buf[ 0 ];
        *( aCardType + 1 ) = theComRC522Buf[ 1 ];
    }
    else
    {
        theStatus = MI_ERR;
    }
    return theStatus;
}

/**
  * @brief  Prevent collision
  * @param  aCardSerialNum:card serial number(4 bytes)
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_PreventCollision( uint8_t *aCardSerialNum )
{
    uint32_t theReceiveDataLength;
    uint8_t theStatus , i , theCardNumCheck;
    uint8_t theComRC522Buf[ MAXRLEN ];
    RC522_ClearBitMask( Status2Reg , 0x08 );
    RC522_WriteDataToRegister( BitFramingReg , 0x00 );
    RC522_ClearBitMask( CollReg , 0x80 );

    theComRC522Buf[ 0 ] = 0x93;
    theComRC522Buf[ 1 ] = 0x20;
    theStatus = RC522_CommunicationOfCard( PCD_TRANSCEIVE ,
                                           theComRC522Buf ,
                                           2 ,
                                           theComRC522Buf ,
                                           &theReceiveDataLength );
    if( theStatus == MI_OK )
    {
        for( i = 0 ; i < 4 ; i++ )
        {
            *( aCardSerialNum + i ) = theComRC522Buf[ i ];      // Read UUID
            theCardNumCheck ^= theComRC522Buf[ i ];
        }

        if( theCardNumCheck != theComRC522Buf[ i ] )
        {
            theStatus = MI_ERR;
        }
    }
    RC522_ClearBitMask( CollReg , 0x80 );
    return theStatus;
}

/**
  * @brief  Select a card
  * @param  aCardSerialNum:card serial number(4 bytes)
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_SelectCard( uint8_t *aCardSerialNum )
{
    uint32_t theReceiveDataLength;
    uint8_t theStatus , i;
    uint8_t theComRC522Buf[ MAXRLEN ];

    theComRC522Buf[ 0 ] = PICC_ANTICOLL1;
    theComRC522Buf[ 1 ] = 0x70;
    theComRC522Buf[ 6 ] = 0;

    for( i = 0 ; i < 4 ; i++ )
    {
        theComRC522Buf[ i + 2 ] = *( aCardSerialNum + i );
        theComRC522Buf[ 6 ] ^= *( aCardSerialNum + i );
    }

    RC522_CalulateCRC( theComRC522Buf , 7 , &theComRC522Buf[ 7 ] );
    RC522_ClearBitMask( Status2Reg , 0x08 );

    theStatus = RC522_CommunicationOfCard( PCD_TRANSCEIVE ,
                                           theComRC522Buf ,
                                           9 ,
                                           theComRC522Buf ,
                                           &theReceiveDataLength );

    if( ( theStatus == MI_OK ) && ( theReceiveDataLength == 0x18 ) )
    {
        theStatus = MI_OK;
    }
    else
    {
        theStatus = MI_ERR;
    }
    return theStatus;
}

/**
  * @brief  Verify card password
  * @param  aVerifyType: if aVerifyType == 0x60, verify the A key
  *                      if aVerifyType == 0x61, verify the B key
  * @param  aAddr: Block addr
  * @param  aKey: The key
  * @param  aCardSerialNum: card serial number(4 bytes)
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_VerifyCardPassword( uint8_t aVerifyType ,
                                  uint8_t aAddr ,
                                  uint8_t *aKey ,
                                  uint8_t *aCardSerialNum )
{
    uint32_t theReceiveDataLength;
    uint8_t theStatus , i;
    uint8_t theComRC522Buf[ MAXRLEN ];

    theComRC522Buf[ 0 ] = aVerifyType;
    theComRC522Buf[ 1 ] = aAddr;

    for( i = 0 ; i < 6 ; i++ )
    {
        theComRC522Buf[ i + 2 ] = *( aKey + i );
    }

    for( i = 0 ; i < 6 ; i++ )
    {
        theComRC522Buf[ i + 8 ] = *( aCardSerialNum + i );
    }

    theStatus = RC522_CommunicationOfCard( PCD_AUTHENT ,
                                           theComRC522Buf ,
                                           12 ,
                                           theComRC522Buf ,
                                           &theReceiveDataLength );

    if( ( theStatus != MI_OK ) || ( !( RC522_ReadDataFromRegister( Status2Reg ) & 0x08 ) ) )
    {
        theStatus = MI_ERR;
    }
    return theStatus;
}

/**
  * @brief  Set card to dormancy state
  * @param  None
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_SetCardToDormancyState( void )
{
    uint32_t theReceiveDataLength;
    uint8_t theComRC522Buf[ MAXRLEN ];

    theComRC522Buf[ 0 ] = PICC_HALT;
    theComRC522Buf[ 1 ] = 0;

    RC522_CalulateCRC( theComRC522Buf , 2 , &theComRC522Buf[ 2 ] );
    RC522_CommunicationOfCard( PCD_TRANSCEIVE ,
                               theComRC522Buf ,
                               4 ,
                               theComRC522Buf ,
                               &theReceiveDataLength );
    return MI_OK;
}

/**
  * @brief  Write data to card block
  * @param  None
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_WriteDataToBlock( uint8_t aAddr , uint8_t *aData )
{
    uint8_t theStatus;
    uint8_t i , theComBuf[ MAXRLEN ];
    uint32_t theReadDataLength;

    theComBuf[ 0 ] = PICC_WRITE;
    theComBuf[ 1 ] = aAddr;

    RC522_CalulateCRC( theComBuf , 2 , &theComBuf[ 2 ] );

    theStatus = RC522_CommunicationOfCard( PCD_TRANSCEIVE ,
                                           theComBuf ,
                                           4 ,
                                           theComBuf ,
                                           &theReadDataLength );

    if( ( theStatus != MI_OK ) || ( theReadDataLength != 4 ) ||
        ( ( theComBuf[ 0 ] & 0x0F ) != 0x0A ) )
    {
        theStatus = MI_ERR;
    }

    if( theStatus == MI_OK )
    {
        for( i = 0 ; i < 16 ; i++ )
        {
            theComBuf[ i ] = *( aData + i );
        }

        RC522_CalulateCRC( theComBuf , 16 , &theComBuf[ 16 ] );

        theStatus = RC522_CommunicationOfCard( PCD_TRANSCEIVE ,
                                               theComBuf ,
                                               18 ,
                                               theComBuf ,
                                               &theReadDataLength );

        if( ( theStatus != MI_OK ) || ( theReadDataLength != 4 ) ||
            ( ( theComBuf[ 0 ] & 0x0F ) != 0x0A ) )
        {
            theStatus = MI_ERR;
        }
    }
    return theStatus;
}

/**
  * @brief  Read block data from card
  * @param  None
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_ReadDataFromBlock( uint8_t aAddr , uint8_t *aData )
{
    uint8_t theStatus;
    uint8_t i , theComBuf[ MAXRLEN ];
    uint32_t theReadDataLength;

    theComBuf[ 0 ] = PICC_READ;
    theComBuf[ 1 ] = aAddr;

    RC522_CalulateCRC( theComBuf , 2 , &theComBuf[ 2 ] );
    theStatus = RC522_CommunicationOfCard( PCD_TRANSCEIVE ,
                                           theComBuf ,
                                           4 ,
                                           theComBuf ,
                                           &theReadDataLength );

    if( ( theStatus == MI_OK ) && ( theReadDataLength == 0x90 ) )
    {
        for( i = 0 ; i < 16 ; i++ )
        {
            *( aData + i ) = theComBuf[ i ];
        }
    }
    else
    {
        theStatus = MI_ERR;
    }
    return theStatus;
}

/**
  * @brief  Write data to register
  * @param  aAddr: Register add
  * @param  aValue: Write data
  * @retval None
  */
static void RC522_WriteDataToRegister( uint8_t aAddr , uint8_t aValue )
{
    uint8_t theAddr;

    theAddr = ( aAddr << 1 ) & 0x7F;
    RC522_CS_Enable();

    SPI_SendByte( RC522_USING_SPI , theAddr );
    SPI_SendByte( RC522_USING_SPI , aValue );

    RC522_CS_Disable();
}

/**
  * @brief  Read data from register
  * @param  aAddr: Register addr
  * @retval Read data
  */
static uint8_t RC522_ReadDataFromRegister( uint8_t aAddr )
{
    uint8_t theAddr , theReadData;

    theAddr = ( ( aAddr << 1) & 0x7E ) | 0x80;
    RC522_CS_Enable();

    SPI_SendByte( RC522_USING_SPI ,theAddr );
    theReadData = SPI_ReadByte( RC522_USING_SPI );

    RC522_CS_Disable();
    return theReadData;
}

/**
  * @brief  Clear register bit mask
  * @param  aAddr: Register addr
  * @param  aMask: Mask value
  * @retval None
  */
static void RC522_ClearBitMask( uint8_t aAddr , uint8_t aMask )
{
    uint8_t theTemp;

    theTemp = RC522_ReadDataFromRegister( aAddr );
    RC522_WriteDataToRegister( aAddr , theTemp & ( ~aMask ) );      // Clear bit mask
}

/**
  * @brief  Set register bit mask
  * @param  aAddr: Register addr
  * @param  aMask: Mask value
  * @retval None
  */
static void RC522_SetBitMask( uint8_t aAddr , uint8_t aMask )
{
    uint8_t theTemp;
    theTemp = RC522_ReadDataFromRegister( aAddr );
    RC522_WriteDataToRegister( aAddr , theTemp | aMask );
}

/**
  * @brief  Open the module antenna
  * @param  None
  * @retval None
  */
static void RC522_OpenAntenna( void )
{
    uint8_t theReadData;
    theReadData = RC522_ReadDataFromRegister( TxControlReg );
    if( !( theReadData & 0x03 ) )
    {
        RC522_SetBitMask( TxControlReg , 0x03 );
    }
}

/**
  * @brief  Close the module antenna
  * @param  None
  * @retval None
  */
static void RC522_CloseAntenna( void )
{
    RC522_ClearBitMask( TxControlReg , 0x03 );
}

/**
  * @brief  RC522 communication with card
  * @param  aCommand: communication command
  * @param  aSendData: send data buffer
  * @param  aSendDataLength: send data length
  * @param  aReceiveData: receive data buffer
  * @param  aReceiveDataLength: receive data length
  * @retval None
  */
static uint8_t RC522_CommunicationOfCard( uint8_t aCommand ,
                                          uint8_t *aSendData ,
                                          uint8_t aSendDataLength ,
                                          uint8_t *aReceiveData ,
                                          uint32_t *aReceiveDataLength )
{
    uint8_t theStatus = MI_ERR;
    uint8_t i , theReadData , theLastBit;
    uint8_t theIrqEn   = 0x00;
    uint8_t theWaitFor = 0x00;
    uint32_t theWaitCount;

    switch( aCommand )
    {
        case PCD_AUTHENT:               // Mifare certification
            theIrqEn   = 0x12;
            theWaitFor = 0x10;
            break;

        case PCD_TRANSCEIVE:            // Send and receive data
            theIrqEn   = 0x77;
            theWaitFor = 0x30;
            break;

        default:
            break;
    }

    RC522_WriteDataToRegister( ComIEnReg , theIrqEn | 0x80 );
    RC522_ClearBitMask( ComIrqReg , 0x80 );
    RC522_WriteDataToRegister( CommandReg , PCD_IDLE );
    RC522_ClearBitMask( FIFOLevelReg , 0x80 );
    for( i = 0 ; i < aSendDataLength ; i++ )
    {
        RC522_WriteDataToRegister( FIFODataReg , aSendData[ i ] );
    }

    RC522_WriteDataToRegister( CommandReg , aCommand );
    if( aCommand == PCD_TRANSCEIVE )
    {
        RC522_SetBitMask( BitFramingReg , 0x80 );
    }

    theWaitCount = 1000;
    do
    {
        theReadData = RC522_ReadDataFromRegister( ComIrqReg );
        theWaitCount --;
    }
    while ( ( theWaitCount != 0 ) && ( !( theReadData & 0x01) ) && ( !( theReadData & theWaitFor ) ) );

    RC522_ClearBitMask( BitFramingReg , 0x80 );

    if( theWaitCount != 0 )
    {
        if( !( RC522_ReadDataFromRegister( ErrorReg ) & 0x1B ) )
        {
            theStatus = MI_OK;
            if( theReadData & theIrqEn & 0x01 )
            {
                theStatus = MI_NOTAGERR;
            }

            if( aCommand == PCD_TRANSCEIVE )
            {
                theReadData = RC522_ReadDataFromRegister( FIFOLevelReg );
                theLastBit = RC522_ReadDataFromRegister( ControlReg ) & 0x07;

                if( theLastBit )
                {
                    *aReceiveDataLength = ( theReadData - 1 ) * 8 + theLastBit;
                }
                else
                {
                    *aReceiveDataLength = theReadData * 8;
                }

                if( theReadData == 0 )
                {
                    theReadData = 1;
                }

                if( theReadData > MAXRLEN )
                {
                    theReadData = MAXRLEN;
                }

                for( i = 0 ; i < theReadData ; i++ )
                {
                    aReceiveData[ i ] = RC522_ReadDataFromRegister( FIFODataReg );
                }
            }
        }
        else
        {
            theStatus = MI_ERR;
        }
    }

    RC522_SetBitMask( ControlReg , 0x80 );          // Stop timer now
    RC522_SetBitMask( CommandReg , PCD_IDLE );

    return theStatus;
}

/**
  * @brief  Calulate CRC
  * @param  aInData: calulate input data
  * @param  aInDataLength: calulate input data length
  * @param  aOutputData: calulate output data
  * @retval None
  */
static void RC522_CalulateCRC( uint8_t *aInData ,
                         uint8_t aInDataLength ,
                         uint8_t *aOutputData )
{
    uint8_t i , theReadData;


    RC522_ClearBitMask( DivIrqReg , 0x04 );
    RC522_WriteDataToRegister( CommandReg , PCD_IDLE );
    RC522_SetBitMask( FIFOLevelReg , 0x80 );

    for( i = 0 ; i < aInDataLength ; i++ )
    {
        RC522_WriteDataToRegister( FIFODataReg , *( aInData + i ) );
    }
    RC522_WriteDataToRegister( CommandReg , PCD_CALCCRC );

    i = 0xFF;
    do
    {
        theReadData = RC522_ReadDataFromRegister( DivIrqReg );
        i--;
    }
    while ( ( i != 0 ) && ( theReadData & 0x04 ) );

    aOutputData[ 0 ] = RC522_ReadDataFromRegister( CRCResultRegL );
    aOutputData[ 1 ] = RC522_ReadDataFromRegister( CRCResultRegM );
}

/**
  * @brief  Configure RC522 module CS pin
  * @param  None
  * @retval None
  */
static void RC522_CS_Configure( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Configure SPI2 pins: CS */
    RC522_GPIO_CS_CLK_FUN( RC522_GPIO_CS_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = RC522_GPIO_CS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = RC522_GPIO_CS_Mode;
    GPIO_Init( RC522_GPIO_CS_PORT , &GPIO_InitStructure );
}

/**
  * @brief  Configure RC522 module RST pin
  * @param  None
  * @retval None
  */
static void RC522_RST_Configure( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Configure SPI_RC522_SPI pins: RST */
    RC522_GPIO_RST_CLK_FUN( RC522_GPIO_RST_CLK , ENABLE );
    GPIO_InitStructure.GPIO_Pin = RC522_GPIO_RST_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = RC522_GPIO_RST_Mode;
    GPIO_Init( RC522_GPIO_RST_PORT , &GPIO_InitStructure );
}

