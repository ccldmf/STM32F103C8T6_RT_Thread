/**
  ******************************************************************************
  * @file    Modules/Flash/flash.c
  * @author  CC
  * @version V1.0.0
  * @date    29-11-2019
  * @brief   flash module driver.
  *          This file provides control the flash module.
  ******************************************************************************
  * @attention
  *
  * STM32f103C8T6 128KB FLASH，20KB RAM，each sector size is 1KB,Program start address:0x8000000
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "flash.h"
#include "stm32f10x_flash.h"

#define FLASH_START_ADDR    ( ( uint32_t )0x8000000 )
#define FLASH_END_ADDR      ( ( uint32_t )( 0x8000000 + FLASH_SECTOR_NUM * FLASH_SECTOR_SIZE ) )
#define FLASH_SECTOR_NUM    128
#define FLASH_SECTOR_SIZE   1024

/**
  * @brief  Read data from flash
  * @param  addr:Read data address
  *         data:Read falsh data to save this parameter
  *         len :Read data length
  * @retval 0:Successful 1:Fail
  */
int ReadFlash( const uint32_t addr , uint8_t *data , const uint32_t len )
{
    memcpy( data , (void*)addr , len );
    return 0;
}

/**
  * @brief  Write data from flash
  * @param  addr:Write data address
  *         data:Write data to flash
  *         len :Write data length
  * @retval 0:Successful other:Success write data len
  */
int WriteFlash( const uint32_t addr , const uint8_t *data , const uint32_t len )
{
    uint16_t i , theWriteData = 0;
    uint32_t theOffsetAddress;
    uint32_t theSectorPosition;
    uint32_t theSectorStartAddress;

    // Check the address of write data is valid.
    if( addr < FLASH_START_ADDR || ( addr + len ) >= FLASH_END_ADDR )
    {
        return -1;
    }
    FLASH_Unlock();
    theOffsetAddress      = addr - FLASH_START_ADDR;
    theSectorPosition     = theOffsetAddress / FLASH_SECTOR_SIZE;
    theSectorStartAddress = theSectorPosition * FLASH_SECTOR_SIZE + FLASH_START_ADDR;
    FLASH_ClearFlag( FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR );
    FLASH_ErasePage( theSectorStartAddress );
    for( i = 0 ; i < len ; i += 2 )
    {
        theWriteData = ( *( data + i + 1 ) << 8) + ( *( data + i ) );
        if( FLASH_ProgramHalfWord( ( uint32_t )( addr + i ) , theWriteData ) != FLASH_COMPLETE )
        {
          return i;
        }
    }
    FLASH_Lock();

    return 0;
}

/**
  * @brief  Erase data
  * @param  addr:Erase data address
  *         len :Erase data length
  * @retval 0:Successful 1:Fail
  */
int EraseFlash( const uint32_t addr , const uint32_t len )
{
    uint8_t i;

    FLASH_Unlock();
    FLASH_ClearFlag( FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR );
    for( i = 0 ; i < len ; ++i )
    {
        if( FLASH_ErasePage( addr + i * FLASH_SECTOR_SIZE ) != FLASH_COMPLETE )
        {
          return 1;
        }
    }
    FLASH_Lock();

    return 0;
}

/******************* (C) COPYRIGHT 2019 CC *****END OF FILE****/
