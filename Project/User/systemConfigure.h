/**
  ******************************************************************************
  * @file    User/systemConfigure.h
  * @author  CC
  * @version V1.0.0
  * @date    06-18-2020
  * @brief   This file provider the system usage resource and macro define.
  *
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SYSTEM_CONFIGURE_H
#define __SYSTEM_CONFIGURE_H

#ifdef __cplusplus
    extern "C" {
#endif


/*-----------------------------------------------------
                    UART Module
-----------------------------------------------------*/

/*-----------------------------------------------------
                    LED Module
-----------------------------------------------------*/

/*-----------------------------------------------------
                    SPI Module
-----------------------------------------------------*/
#define    USING_SPI
#define    USING_SPI1
#define    USING_SPI2

#ifdef USING_SPI
#ifdef USING_SPI1
// Clock, SCK pin of module and connect to SCK pin of SPI for the MCU.
#define    SPI1_GPIO_SCK_CLK_FUN     RCC_APB2PeriphClockCmd
#define    SPI1_GPIO_SCK_CLK         RCC_APB2Periph_GPIOA
#define    SPI1_GPIO_SCK_PORT        GPIOA
#define    SPI1_GPIO_SCK_PIN         GPIO_Pin_5
#define    SPI1_GPIO_SCK_Mode        GPIO_Mode_Out_PP

// Data input, MOSI pin of module and connect to MOSI pin of SPI for the MCU.
#define    SPI1_GPIO_MOSI_CLK_FUN    RCC_APB2PeriphClockCmd
#define    SPI1_GPIO_MOSI_CLK        RCC_APB2Periph_GPIOA
#define    SPI1_GPIO_MOSI_PORT       GPIOA
#define    SPI1_GPIO_MOSI_PIN        GPIO_Pin_7
#define    SPI1_GPIO_MOSI_Mode       GPIO_Mode_Out_PP

// Data output, MISO pin of module and connect to MISO pin of SPI for the MCU.
#define    SPI1_GPIO_MISO_CLK_FUN    RCC_APB2PeriphClockCmd
#define    SPI1_GPIO_MISO_CLK        RCC_APB2Periph_GPIOA
#define    SPI1_GPIO_MISO_PORT       GPIOA
#define    SPI1_GPIO_MISO_PIN        GPIO_Pin_6
#define    SPI1_GPIO_MISO_Mode       GPIO_Mode_IN_FLOATING
#endif

#ifdef USING_SPI2
// Clock, SCK pin of module and connect to SCK pin of SPI for the MCU.
#define    SPI2_GPIO_SCK_CLK_FUN     RCC_APB2PeriphClockCmd
#define    SPI2_GPIO_SCK_CLK         RCC_APB2Periph_GPIOB
#define    SPI2_GPIO_SCK_PORT        GPIOB
#define    SPI2_GPIO_SCK_PIN         GPIO_Pin_13
#define    SPI2_GPIO_SCK_Mode        GPIO_Mode_Out_PP

// Data input, MOSI pin of module and connect to MOSI pin of SPI for the MCU.
#define    SPI2_GPIO_MOSI_CLK_FUN    RCC_APB2PeriphClockCmd
#define    SPI2_GPIO_MOSI_CLK        RCC_APB2Periph_GPIOB
#define    SPI2_GPIO_MOSI_PORT       GPIOB
#define    SPI2_GPIO_MOSI_PIN        GPIO_Pin_15
#define    SPI2_GPIO_MOSI_Mode       GPIO_Mode_Out_PP

// Data output, MISO pin of module and connect to MISO pin of SPI for the MCU.
#define    SPI2_GPIO_MISO_CLK_FUN    RCC_APB2PeriphClockCmd
#define    SPI2_GPIO_MISO_CLK        RCC_APB2Periph_GPIOB
#define    SPI2_GPIO_MISO_PORT       GPIOB
#define    SPI2_GPIO_MISO_PIN        GPIO_Pin_14
#define    SPI2_GPIO_MISO_Mode       GPIO_Mode_IN_FLOATING
#endif
#endif
/*-----------------------------------------------------
                    End of SPI Module
-----------------------------------------------------*/


/*-----------------------------------------------------
                    RC522 Module
-----------------------------------------------------*/
// Set RC522 module using SPI port
#define    RC522_USING_SPI            SPI1_PORT

// Select Chip, SDA pin of RC522 and connect to universal IO pin of MCU.
#define    RC522_GPIO_CS_CLK_FUN      RCC_APB2PeriphClockCmd
#define    RC522_GPIO_CS_CLK          RCC_APB2Periph_GPIOB
#define    RC522_GPIO_CS_PORT         GPIOB
#define    RC522_GPIO_CS_PIN          GPIO_Pin_0
#define    RC522_GPIO_CS_Mode         GPIO_Mode_Out_PP

// Reset, RST pin of RC522 module and connect to universal IO pin of MCU.
#define    RC522_GPIO_RST_CLK_FUN     RCC_APB2PeriphClockCmd
#define    RC522_GPIO_RST_CLK         RCC_APB2Periph_GPIOB
#define    RC522_GPIO_RST_PORT        GPIOB
#define    RC522_GPIO_RST_PIN         GPIO_Pin_1
#define    RC522_GPIO_RST_Mode        GPIO_Mode_Out_PP
/*-----------------------------------------------------
                End of RC522 Module
-----------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_CONFIGURE_H */
