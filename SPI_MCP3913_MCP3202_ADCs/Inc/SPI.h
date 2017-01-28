#ifndef __SPI_H
#define __SPI_H


//SPI_HandleTypeDef Spi2Handle;

/* Definition for SPI2 hardware and clock resources */
#define SPI3_CLK_ENABLE()                __SPI3_CLK_ENABLE()
#define SPI3_SCK_GPIO_CLK_ENABLE()       __GPIOC_CLK_ENABLE()
#define SPI3_MISO_GPIO_CLK_ENABLE()      __GPIOC_CLK_ENABLE() 
#define SPI3_MOSI_GPIO_CLK_ENABLE()      __GPIOC_CLK_ENABLE() 

/* Definition for SPI3 Pins */
#define SPI3_SCK_PIN                     GPIO_PIN_10
#define SPI3_SCK_GPIO_PORT               GPIOC
#define SPI3_SCK_AF                      GPIO_AF6_SPI3
#define SPI3_MISO_PIN                    GPIO_PIN_11
#define SPI3_MISO_GPIO_PORT              GPIOC
#define SPI3_MISO_AF                     GPIO_AF6_SPI3
#define SPI3_MOSI_PIN                    GPIO_PIN_12
#define SPI3_MOSI_GPIO_PORT              GPIOC
#define SPI3_MOSI_AF                     GPIO_AF6_SPI3

#define SPI3_CS_BM_CLK_ENABLE()            __GPIOC_CLK_ENABLE() //PC8
#define SPI3_CS_EM_CLK_ENABLE()            __GPIOC_CLK_ENABLE()  //PC9


#endif /* __cplusplus */