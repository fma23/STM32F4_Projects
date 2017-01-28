/**
  ******************************************************************************
  * File Name          : stm32f4xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "I2C.h"
#include "SPI.h"


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
	 /* TIM3 Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
	
	 /* Set Interrupt Group Priority */ 
	  HAL_NVIC_SetPriority(TIM3_IRQn, 4, 0);
	  
	  /* Enable the TIMx global Interrupt */
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
    __HAL_RCC_TIM3_CLK_DISABLE();

}


/**
  * @brief SPI MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

	/* Enable SPI clock */
	__SPI3_CLK_ENABLE();

	/* Enable GPIOs clock */
	__GPIOC_CLK_ENABLE();
	
 /* SPI3 SCK GPIO pin configuration  */
	GPIO_InitStruct.Pin       = SPI3_SCK_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	GPIO_InitStruct.Alternate = SPI3_SCK_AF;
	
	HAL_GPIO_Init(SPI3_SCK_GPIO_PORT, &GPIO_InitStruct);
		
	/* SPI3 MISO GPIO pin configuration  */
	GPIO_InitStruct.Pin = SPI3_MISO_PIN;
	GPIO_InitStruct.Alternate = SPI3_MISO_AF;
	HAL_GPIO_Init(SPI3_MISO_GPIO_PORT, &GPIO_InitStruct);
	
	/* SPI3 MOSI GPIO pin configuration  */
	GPIO_InitStruct.Pin = SPI3_MOSI_PIN;
	GPIO_InitStruct.Alternate = SPI3_MOSI_AF;
	HAL_GPIO_Init(SPI3_MOSI_GPIO_PORT, &GPIO_InitStruct);
					
	}

	/**
  * @brief SPI MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO configuration to its default state
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
	 
		/*Reset peripherals */
	__SPI3_FORCE_RESET();
	__SPI3_RELEASE_RESET();

	/*Disable peripherals and GPIO Clocks */
	HAL_GPIO_DeInit(SPI3_SCK_GPIO_PORT, SPI3_SCK_PIN);
	
	/* Configure SPI MISO as alternate function  */
	HAL_GPIO_DeInit(SPI3_MISO_GPIO_PORT, SPI3_MISO_PIN);
	
	/* Configure SPI MOSI as alternate function  */
	HAL_GPIO_DeInit(SPI3_MOSI_GPIO_PORT, SPI3_MOSI_PIN);
			 	 
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
