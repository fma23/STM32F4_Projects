#ifndef __SPI_H
#define __SPI_H

//#include "stm32f4xx_hal_spi.h"

//SPI_HandleTypeDef Spi2Handle;

/* Definition for SPI2 hardware and clock resources */
#define SPI2_CLK_ENABLE()                __SPI2_CLK_ENABLE()
#define SPI2_SCK_GPIO_CLK_ENABLE()       __GPIOI_CLK_ENABLE()
#define SPI2_MISO_GPIO_CLK_ENABLE()      __GPIOI_CLK_ENABLE() 
#define SPI2_MOSI_GPIO_CLK_ENABLE()      __GPIOI_CLK_ENABLE() 


#define SPI2_CS_CLK_ENABLE()            __GPIOI_CLK_ENABLE() 
#define SPI2_RS_CLK_ENABLE()            __GPIOA_CLK_ENABLE()  //PA9


/* Definition for SPI2 Pins */
#define SPI2_SCK_PIN                     GPIO_PIN_1
#define SPI2_SCK_GPIO_PORT               GPIOI
#define SPI2_SCK_AF                      GPIO_AF5_SPI2
#define SPI2_MISO_PIN                    GPIO_PIN_2
#define SPI2_MISO_GPIO_PORT              GPIOI
#define SPI2_MISO_AF                     GPIO_AF5_SPI2
#define SPI2_MOSI_PIN                    GPIO_PIN_3
#define SPI2_MOSI_GPIO_PORT              GPIOI
#define SPI2_MOSI_AF                     GPIO_AF5_SPI2

#define SPI2_CS                          PORTI_BIT1
#define SPI2_RES                         PORTA_BIT9


#endif /* __cplusplus */