#ifndef __I2C_H
#define __I2C_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/* Definition for I2Cx clock resources */
#define I2Cx                             I2C1
#define I2Cx_CLK_ENABLE()                __I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE()       __GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE()       __GPIOB_CLK_ENABLE() 

#define I2Cx_FORCE_RESET()               __I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()             __I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define I2Cx_SCL_PIN                    GPIO_PIN_6
#define I2Cx_SCL_GPIO_PORT              GPIOB
#define I2Cx_SCL_AF                     GPIO_AF4_I2C1
#define I2Cx_SDA_PIN                    GPIO_PIN_9
#define I2Cx_SDA_GPIO_PORT              GPIOB
#define I2Cx_SDA_AF                     GPIO_AF4_I2C1

/* Definition for I2Cx's NVIC */
#define I2Cx_EV_IRQn                    I2C1_EV_IRQn
#define I2Cx_EV_IRQHandler              I2C1_EV_IRQHandler
#define I2Cx_ER_IRQn                    I2C1_ER_IRQn
#define I2Cx_ER_IRQHandler              I2C1_ER_IRQHandler

/* Size of Transmission buffer */
#define TXBUFFERSIZE                      (COUNTOF(aTxBuffer) - 1)
/* Size of Reception buffer */
#define RXBUFFERSIZE                      TXBUFFERSIZE
  
/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */

#define I2C_ADDRESS        0x30F

#endif /* __cplusplus */