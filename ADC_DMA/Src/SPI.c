#include "main.h"

SPI_HandleTypeDef Spi2Handle;










/**
  * SPI2 error handler
  */
void SPI2Error_Handler(void) 
{
   while(1)
  {
  }
	
 } 

 /**
  * SPI2 Configuration
  */
void SPI2_Config(void){
	
	
  Spi2Handle.Instance               = SPI2;
  
	Spi2Handle.Init.Mode = SPI_MODE_MASTER;
	
  Spi2Handle.Instance               = SPI2;
  Spi2Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; // 42MHz/256=167kHz < 400kHz
  Spi2Handle.Init.Direction         = SPI_DIRECTION_2LINES;
  Spi2Handle.Init.CLKPhase          = SPI_PHASE_2EDGE;
  Spi2Handle.Init.CLKPolarity       = SPI_POLARITY_HIGH;
  Spi2Handle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLED;
  Spi2Handle.Init.CRCPolynomial     = 7;
  Spi2Handle.Init.DataSize          = SPI_DATASIZE_8BIT;
  Spi2Handle.Init.FirstBit          = SPI_FIRSTBIT_LSB;
  Spi2Handle.Init.NSS               = SPI_NSS_HARD_OUTPUT; //SPI_NSS_SOFT;
  Spi2Handle.Init.TIMode            = SPI_TIMODE_DISABLED;

	if(HAL_SPI_Init(&Spi2Handle) != HAL_OK)
  {
    /* Initialization Error */
    SPI2Error_Handler();
  }
	
}

/**
  * SPI2 Chip Select, and LCD reset line configuration
  */
void SPI_CS_RS_Config(void){
	
	/* Enable both GPIO clock */
	__GPIOA_CLK_ENABLE();
	__GPIOI_CLK_ENABLE();
	
		/* Select output mode (01) on PA9: for the RESET*/
	GPIOA->MODER  &= ~(3UL << 2 * 9);
  GPIOA->MODER  |=  (1UL << 2 * 9);
  GPIOA->OTYPER &= ~(1UL <<     9);
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER9)) | (GPIO_MODER_MODER9_0); 
	
	/* Select output mode (01) on PI5: for the Chip Select*/    
	GPIOI->MODER  &= ~(3UL << 2 * 5);
  GPIOI->MODER  |=  (1UL << 2 * 5);
  GPIOI->OTYPER &= ~(1UL <<     5);
	GPIOI->MODER = (GPIOI->MODER & ~(GPIO_MODER_MODER5)) | (GPIO_MODER_MODER5_0); 
	
	
}