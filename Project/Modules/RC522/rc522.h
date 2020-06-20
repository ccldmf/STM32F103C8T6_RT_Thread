/**
  ******************************************************************************
  * @file    Modules/RC522/rc522.h
  * @author  CC
  * @version V1.0.0
  * @date    06-19-2020
  * @brief   This file provider the RC522 module public API interface.
  *
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RC522_H
#define __RC522_H

#ifdef __cplusplus
    extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/**
  * @brief  RC522 module init
  * @param  None
  * @retval None
  */
void RC522_Init( void );

/**
  * @brief  RC522 module reset
  * @param  None
  * @retval None
  */
void RC522_Reset( void );

/**
  * @brief  Set RC522 module work type
  * @param  aType: work type
  * @retval None
  */
void RC522_ConfigType( uint8_t aType );

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
uint8_t RC522_LookForCard( uint8_t aRequstCode , uint8_t *aCardType );

/**
  * @brief  Prevent collision
  * @param  aCardSerialNum:card serial number(4 bytes)
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_PreventCollision( uint8_t *aCardSerialNum );

/**
  * @brief  Select a card
  * @param  aCardSerialNum:card serial number(4 bytes)
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_SelectCard( uint8_t *aCardSerialNum );

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
                                  uint8_t aAddr,
                                  uint8_t *aKey ,
                                  uint8_t *aCardSerialNum );

/**
  * @brief  Set card to dormancy state
  * @param  None
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_SetCardToDormancyState( void );

/**
  * @brief  Write data to card block
  * @param  None
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_WriteDataToBlock( uint8_t aAddr , uint8_t *aData );

/**
  * @brief  Read block data from card
  * @param  None
  * @retval Successful: MI_OK  fail: MI_ERR
  */
uint8_t RC522_ReadDataFromBlock( uint8_t aAddr , uint8_t *aData );


/*-----------------------------------------------------
        RC522 module macro define function
-----------------------------------------------------*/
#define    RC522_CS_Enable()        GPIO_ResetBits ( RC522_GPIO_CS_PORT , RC522_GPIO_CS_PIN )
#define    RC522_CS_Disable()       GPIO_SetBits ( RC522_GPIO_CS_PORT , RC522_GPIO_CS_PIN )

#define    RC522_Reset_Enable()     GPIO_ResetBits( RC522_GPIO_RST_PORT , RC522_GPIO_RST_PIN )
#define    RC522_Reset_Disable()    GPIO_SetBits ( RC522_GPIO_RST_PORT , RC522_GPIO_RST_PIN )

#define    RC522_SCK_0()            GPIO_ResetBits( RC522_GPIO_SCK_PORT , RC522_GPIO_SCK_PIN )
#define    RC522_SCK_1()            GPIO_SetBits ( RC522_GPIO_SCK_PORT , RC522_GPIO_SCK_PIN )

#define    RC522_MOSI_0()           GPIO_ResetBits( RC522_GPIO_MOSI_PORT , RC522_GPIO_MOSI_PIN )
#define    RC522_MOSI_1()           GPIO_SetBits ( RC522_GPIO_MOSI_PORT , RC522_GPIO_MOSI_PIN )

#define    RC522_MISO_GET()         GPIO_ReadInputDataBit ( RC522_GPIO_MISO_PORT , RC522_GPIO_MISO_PIN )

/*-----------------------------------------------------
        RC522 module register define
-----------------------------------------------------*/
// PAGE 0
#define    RFU00                0x00
#define    CommandReg           0x01
#define    ComIEnReg            0x02
#define    DivlEnReg            0x03
#define    ComIrqReg            0x04
#define    DivIrqReg            0x05
#define    ErrorReg             0x06
#define    Status1Reg           0x07
#define    Status2Reg           0x08
#define    FIFODataReg          0x09
#define    FIFOLevelReg         0x0A
#define    WaterLevelReg        0x0B
#define    ControlReg           0x0C
#define    BitFramingReg        0x0D
#define    CollReg              0x0E
#define    RFU0F                0x0F
// PAGE 1
#define    RFU10                0x10
#define    ModeReg              0x11
#define    TxModeReg            0x12
#define    RxModeReg            0x13
#define    TxControlReg         0x14
#define    TxAutoReg            0x15
#define    TxSelReg             0x16
#define    RxSelReg             0x17
#define    RxThresholdReg       0x18
#define    DemodReg             0x19
#define    RFU1A                0x1A
#define    RFU1B                0x1B
#define    MifareReg            0x1C
#define    RFU1D                0x1D
#define    RFU1E                0x1E
#define    SerialSpeedReg       0x1F
// PAGE 2
#define    RFU20                0x20
#define    CRCResultRegM        0x21
#define    CRCResultRegL        0x22
#define    RFU23                0x23
#define    ModWidthReg          0x24
#define    RFU25                0x25
#define    RFCfgReg             0x26
#define    GsNReg               0x27
#define    CWGsCfgReg           0x28
#define    ModGsCfgReg          0x29
#define    TModeReg             0x2A
#define    TPrescalerReg        0x2B
#define    TReloadRegH          0x2C
#define    TReloadRegL          0x2D
#define    TCounterValueRegH    0x2E
#define    TCounterValueRegL    0x2F
// PAGE 3
#define    RFU30                0x30
#define    TestSel1Reg          0x31
#define    TestSel2Reg          0x32
#define    TestPinEnReg         0x33
#define    TestPinValueReg      0x34
#define    TestBusReg           0x35
#define    AutoTestReg          0x36
#define    VersionReg           0x37
#define    AnalogTestReg        0x38
#define    TestDAC1Reg          0x39
#define    TestDAC2Reg          0x3A
#define    TestADCReg           0x3B
#define    RFU3C                0x3C
#define    RFU3D                0x3D
#define    RFU3E                0x3E
#define    RFU3F                0x3F

/*-----------------------------------------------------
            RC522 Command
-----------------------------------------------------*/
#define    PCD_IDLE             0x00
#define    PCD_AUTHENT          0x0E
#define    PCD_RECEIVE          0x08
#define    PCD_TRANSMIT         0x04
#define    PCD_TRANSCEIVE       0x0C
#define    PCD_RESETPHASE       0x0F
#define    PCD_CALCCRC          0x03

#define    PICC_REQIDL          0x26
#define    PICC_REQALL          0x52
#define    PICC_ANTICOLL1       0x93
#define    PICC_ANTICOLL2       0x95
#define    PICC_AUTHENT1A       0x60
#define    PICC_AUTHENT1B       0x61
#define    PICC_READ            0x30
#define    PICC_WRITE           0xA0
#define    PICC_DECREMENT       0xC0
#define    PICC_INCREMENT       0xC1
#define    PICC_RESTORE         0xC2
#define    PICC_TRANSFER        0xB0
#define    PICC_HALT            0x50

/*-----------------------------------------------------
        RC522 return error code
-----------------------------------------------------*/
#define    MI_OK                0x26
#define    MI_NOTAGERR          0xcc
#define    MI_ERR               0xbb


#ifdef __cplusplus
}
#endif

#endif /* __RC522_H */
