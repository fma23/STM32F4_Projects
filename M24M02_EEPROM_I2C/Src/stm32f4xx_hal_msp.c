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
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*##-1- Enable GPIO Clocks #################################################*/
  /* Enable GPIO TX/RX clock */
  I2Cx_SCL_GPIO_CLK_ENABLE();
  I2Cx_SDA_GPIO_CLK_ENABLE();
	__GPIOA_CLK_ENABLE();
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* I2C TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = I2Cx_SCL_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = I2Cx_SCL_AF;
  HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);
    
  /* I2C RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = I2Cx_SDA_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;//
  GPIO_InitStruct.Pull      = GPIO_PULLUP;//
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;//
	GPIO_InitStruct.Alternate = I2Cx_SDA_AF;
  HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);

  /* define PA10 for EEPROM WR as an input  */

//  GPIO_InitStruct.Pin       = GPIO_PIN_10;
//  GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_OD;
//  GPIO_InitStruct.Pull      = GPIO_PULLUP;
//  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*##-3- Enable I2C peripherals Clock #######################################*/
  /* Enable I2C1 clock */
  I2Cx_CLK_ENABLE();

}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
