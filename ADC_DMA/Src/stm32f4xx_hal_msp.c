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
					SPI2_CLK_ENABLE(); 
					
					__GPIOI_CLK_ENABLE();
					SPI2_RS_CLK_ENABLE();            //__GPIOA_CLK_ENABLE()
		
				 /* SPI2 SCK GPIO pin configuration  */
					GPIO_InitStruct.Pin       = SPI2_SCK_PIN;
					GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
					GPIO_InitStruct.Pull      = GPIO_PULLUP;
					GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
					GPIO_InitStruct.Alternate = SPI2_SCK_AF;
					
					HAL_GPIO_Init(SPI2_SCK_GPIO_PORT, &GPIO_InitStruct);
						
					/* SPI2 MISO GPIO pin configuration  */
					GPIO_InitStruct.Pin = SPI2_MISO_PIN;
					GPIO_InitStruct.Alternate = SPI2_MISO_AF;
					HAL_GPIO_Init(SPI2_MISO_GPIO_PORT, &GPIO_InitStruct);
					
					/* SPI2 MOSI GPIO pin configuration  */
					GPIO_InitStruct.Pin = SPI2_MOSI_PIN;
					GPIO_InitStruct.Alternate = SPI2_MOSI_AF;
					HAL_GPIO_Init(SPI2_MOSI_GPIO_PORT, &GPIO_InitStruct);
					
					
					/* SPI2 CHIP Select GPIO pin configuration  */
					GPIO_InitStruct.Pin       = GPIO_PIN_5;
					GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
					GPIO_InitStruct.Pull      = GPIO_PULLUP;
					GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;

					HAL_GPIO_Init(SPI2_SCK_GPIO_PORT, &GPIO_InitStruct);

					/* RESET GPIO pin configuration  */
					GPIO_InitStruct.Pin       = GPIO_PIN_9;
					GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
					GPIO_InitStruct.Pull      = GPIO_PULLUP;
					GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
					
					HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
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
	
				/*##-1- Reset peripherals */
				__SPI2_FORCE_RESET();
				__SPI2_RELEASE_RESET();

				/*Disable peripherals and GPIO Clocks */
				/* Configure SPI SCK as alternate function  */
				HAL_GPIO_DeInit(SPI2_SCK_GPIO_PORT, SPI2_SCK_PIN);
				/* Configure SPI MISO as alternate function  */
				HAL_GPIO_DeInit(SPI2_MISO_GPIO_PORT, SPI2_MISO_PIN);
				/* Configure SPI MOSI as alternate function  */
				HAL_GPIO_DeInit(SPI2_MOSI_GPIO_PORT, SPI2_MOSI_PIN);
				
}

/**
  * @brief ADC MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO configuration to its default state
  * @param hspi: SPI handle pointer
  * @retval None
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	
	GPIO_InitTypeDef GPIO_InitStructure1;
  GPIO_InitTypeDef GPIO_InitStructure2;
	
	static DMA_HandleTypeDef  hdma_adc3;

		__GPIOF_CLK_ENABLE();
    __ADC3_CLK_ENABLE();
    __DMA2_CLK_ENABLE();
	
    GPIO_InitStructure1.Pin = GPIO_PIN_3 |GPIO_PIN_4;  //ADC3-ch9; ADC3-Ch14;
    GPIO_InitStructure1.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure1.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStructure1);
	
	
	  /*Configure the DMA streams */
  /* Set the parameters to be configured */
  hdma_adc3.Instance = DMA2_Stream1 ;
  
  hdma_adc3.Init.Channel  = DMA_CHANNEL_2;
  hdma_adc3.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_adc3.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_adc3.Init.MemInc = DMA_MINC_ENABLE;
  hdma_adc3.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_adc3.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_adc3.Init.Mode = DMA_CIRCULAR; 
  hdma_adc3.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_adc3.Init.FIFOMode = DMA_FIFOMODE_DISABLE;         
  hdma_adc3.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL;
  hdma_adc3.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_adc3.Init.PeriphBurst = DMA_PBURST_SINGLE; 

  HAL_DMA_Init(&hdma_adc3);
    
  /* Associate the initialized DMA handle to the the ADC handle */
  __HAL_LINKDMA(hadc, DMA_Handle, hdma_adc3);
	
	
	 /*Configure the NVIC for DMA */
  /* NVIC configuration for DMA transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);   
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
}
  
/**
  * @brief ADC MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO to their default state
  * @param hadc: ADC handle pointer
  * @retval None
  */
void HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc)
{
  
  /*Reset peripherals*/
	__ADC3_CLK_DISABLE();
	
  __ADC_FORCE_RESET();
  __ADC_RELEASE_RESET();
	

  
  /*Disable the DMA Streams */
  /* De-Initialize the DMA Stream associate to transmission process */
 // HAL_DMA_DeInit(&hdma_adc); 
    
  /*Disable the NVIC for DMA*/
  HAL_NVIC_DisableIRQ(DMA2_Stream0_IRQn);
	
  /*Disable peripherals and GPIO Clocks */
  /* De-initialize the ADC3 Channel8 GPIO pin */
  HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5);
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6);
	
	HAL_GPIO_DeInit(GPIOF, GPIO_PIN_3);
	HAL_GPIO_DeInit(GPIOF, GPIO_PIN_4);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
