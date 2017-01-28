#include "main.h"

SPI_HandleTypeDef Spi3Handle;




/**
  * SPI2 error handler
  */
void SPI3Error_Handler(void) 
{
   while(1)
  {
  }
	
 } 

 /**
  * SPI2 Configuration
  */
void SPI3_Config(void){
	
	
	Spi3Handle.Instance               = SPI3;
  
	Spi3Handle.Init.Mode = SPI_MODE_MASTER;
	
  Spi3Handle.Instance               = SPI3;
  Spi3Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; // 42MHz/256=167kHz < 400kHz
  Spi3Handle.Init.Direction         = SPI_DIRECTION_2LINES;
  Spi3Handle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  Spi3Handle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  Spi3Handle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLED;
  Spi3Handle.Init.CRCPolynomial     = 7;
  Spi3Handle.Init.DataSize          = SPI_DATASIZE_8BIT;
  Spi3Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  Spi3Handle.Init.NSS               = SPI_NSS_HARD_OUTPUT;
	Spi3Handle.Init.TIMode            = SPI_TIMODE_DISABLED;

	if(HAL_SPI_Init(&Spi3Handle) != HAL_OK)
  {
    /* Initialization Error */
    SPI3Error_Handler();
  }

}

/**
  * SPI2 Chip Select, and LCD reset line configuration
  */
void SPI3_CS_RS_Config(void){
	
	/* Enable both GPIO clock */
	__GPIOC_CLK_ENABLE();
	__GPIOF_CLK_ENABLE();
	
		/* Select output mode (01) on PC7: for Chip Select for Energy meter MCP3913*/
	GPIOC->MODER  &= ~(3UL << 2 * 7);
  GPIOC->MODER  |=  (1UL << 2 * 7);
  GPIOC->OTYPER &= ~(1UL <<     7);
	GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER7)) | (GPIO_MODER_MODER7_0); 
	
	/* Select output mode (01) on PC9: for Chip Select for battery Monitor MCP3204*/
	GPIOC->MODER  &= ~(3UL << 2 * 9);
  GPIOC->MODER  |=  (1UL << 2 * 9);
  GPIOC->OTYPER &= ~(1UL <<     9);
	GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER9)) | (GPIO_MODER_MODER9_0);  
	
	/* Select output mode (01) on PF11: for Chip Select for Energy meter MCP3913 reset line*/
	GPIOF->MODER  &= ~(3UL << 2 * 11);
  GPIOF->MODER  |=  (1UL << 2 * 11);
  GPIOF->OTYPER &= ~(1UL <<     11);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER11)) | (GPIO_MODER_MODER11_0); 
	
	/* Select output mode (01) on PF14: for Chip Select for Energy meter MCP3913 Isolated output enable*/
	GPIOF->MODER  &= ~(3UL << 2 * 14);
  GPIOF->MODER  |=  (1UL << 2 * 14);
  GPIOF->OTYPER &= ~(1UL <<     14);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER14)) | (GPIO_MODER_MODER14_0); 

	/* Select output mode (01) on PF15: for Chip Select for battery monitor MCP3204 Isolated output enable*/
	GPIOF->MODER  &= ~(3UL << 2 * 15);
  GPIOF->MODER  |=  (1UL << 2 * 15);
  GPIOF->OTYPER &= ~(1UL <<     15);
	GPIOF->MODER = (GPIOF->MODER & ~(GPIO_MODER_MODER15)) | (GPIO_MODER_MODER15_0); 
}