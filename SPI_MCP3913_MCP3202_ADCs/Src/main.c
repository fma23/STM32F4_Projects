/**
  ******************************************************************************
  * Author             : Farid Mabrouk
	* File Name          : main.c
  * Description        : Main program 
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
#include "main.h"
#include "MCP3913.h"
#include <stdbool.h>


TIM_HandleTypeDef Tim3Handle;
uint32_t uwPrescalerValue = 0;
extern volatile bool Timer3Flag;

void SystemClock_Config(void);
void Error_Handler(void);

int main(void)
{

	static uint8_t counter=0; 
	uint8_t register_address=0;
	
  /*initialize the HAL Library */
  HAL_Init();

	/*System Clock Config */
  SystemClock_Config();
	
	/*GPIOs and LED Config */
	Configure_LEDs();

	/*SPI Config */
	SPI3_Config();
	SPI3_CS_RS_Config();
	
	/*TIMER3 Config */
	Timer3_Interrupt_Config();
	
  
	/*wait for interrupts*/
  while (1)
  {
    if(Timer3Flag==true)
		{
			Timer3Flag=false; 
			
			counter++;
	
			GPIOC->ODR |= GPIO_ODR_ODR_7; // de-assert chip select for nergy meter MCP3913;
			GPIOC->ODR |= GPIO_ODR_ODR_9; // de-assert chip select for battery monitor MCP3204;
			
	     //Request an ADC channel read
			 if (counter==1)
			 {			
			 GPIOF->ODR |= GPIO_ODR_ODR_14; // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~GPIO_ODR_ODR_15; // Disable MCP3204 ADC isolated output;	 
		
			 register_address=0;
			 MCP3913A_ReadRequest(&register_address);     // register(0x00);
			 }
			 else if (counter==2)
			 {

			 GPIOF->ODR |= GPIO_ODR_ODR_14; // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~GPIO_ODR_ODR_15; // Disable MCP3204 ADC isolated output;
          
			 register_address=0x01;					 
			 MCP3913A_ReadRequest(&register_address);     // register(0x01); 
			 }
			 else if (counter==3)
			 {
						
			 GPIOF->ODR |= GPIO_ODR_ODR_14; // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~GPIO_ODR_ODR_15; // Disable MCP3204 ADC isolated output;
					
			 register_address=0x02;
			 MCP3913A_ReadRequest(&register_address);     // register(0x02)
			 }
			 else if (counter==4)
			 {
						
			 GPIOF->ODR |= GPIO_ODR_ODR_14; // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~GPIO_ODR_ODR_15; // Disable MCP3204 ADC isolated output;
					
       register_address=0x03;						
			 MCP3913A_ReadRequest(&register_address);     // register(0x03);
			 }
			 else if (counter==5)
			 {		
			 GPIOF->ODR |= GPIO_ODR_ODR_14; // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~GPIO_ODR_ODR_15; // Disable MCP3204 ADC isolated output;
				 
       register_address=0x04;						
			 MCP3913A_ReadRequest(&register_address);     // register(0x04);
			 }
			 else if (counter==6)
			 {		
			 GPIOF->ODR |= GPIO_ODR_ODR_14; // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~GPIO_ODR_ODR_15; // Disable MCP3204 ADC isolated output;
					
       register_address=0x05;						
			 MCP3913A_ReadRequest(&register_address);     // register(0x05);
			 }
			 
			 //Battery Monitor ADC MCP3204
			 else if (counter==7)
			 {
			 GPIOF->ODR &= ~ GPIO_ODR_ODR_14; // Disable MCP3913 ADC isolated output;
			 GPIOF->ODR |= GPIO_ODR_ODR_15;   // Enable MCP3204 ADC isolated output;;
			
			 MCP3204_ReadRequest(0x00);       // Read Channel 0
			 }
			 else if (counter==8)
			 {		
       GPIOF->ODR &= ~ GPIO_ODR_ODR_14; // Disable MCP3913 ADC isolated output;
			 GPIOF->ODR |= GPIO_ODR_ODR_15;   // Enable MCP3204 ADC isolated output;;		
			 
			 MCP3204_ReadRequest(0x01);       // Read Channel 1
			 }
		   else if (counter==9)
			 {	
       GPIOF->ODR &= ~GPIO_ODR_ODR_14;  // Disable MCP3913 ADC isolated output;
			 GPIOF->ODR |= GPIO_ODR_ODR_15;    // Enable MCP3204 ADC isolated output;;	
						
			 MCP3204_ReadRequest(0x02);       // Read Channel 2
			 }
			 else if (counter==10)
			 {	
       GPIOF->ODR &= ~ GPIO_ODR_ODR_14;   // Disable MCP3913 ADC isolated output;
			 GPIOF->ODR |= GPIO_ODR_ODR_15;     // Enable MCP3204 ADC isolated output;
			 
			 MCP3204_ReadRequest(0x03);         // Read Channel 3
			 }
			 else if (counter==11)
			 {
       GPIOF->ODR |=  GPIO_ODR_ODR_14;    // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~GPIO_ODR_ODR_15;    // Disable MCP3204 ADC isolated output;
						
			 register_address=0x0C;
			 MCP3913A_ReadRequest(&register_address);      // register0
			 }
			 else if (counter==12)
			 {	
       GPIOF->ODR |=  GPIO_ODR_ODR_14;   // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~ GPIO_ODR_ODR_15;  // Disable MCP3204 ADC isolated output;					
						
			 register_address=0x0D;
			 MCP3913A_ReadRequest(&register_address);      // register1
       }
			 else if (counter==13)
			 {
       GPIOF->ODR |=  GPIO_ODR_ODR_14;   // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~GPIO_ODR_ODR_15;   // Disable MCP3204 ADC isolated output;
						
			 register_address=0x0E;
			 MCP3913A_ReadRequest(&register_address);      // status Comm register
			 }
			 else if (counter==14)
			 {
       GPIOF->ODR |=  GPIO_ODR_ODR_14;   // Enable MCP3913 ADC isolated output;
			 GPIOF->ODR &= ~GPIO_ODR_ODR_15;   // Disable MCP3204 ADC isolated output;
						
			 register_address=0x1F;
			 MCP3913A_ReadRequest(&register_address);      //  LOCK register
		    
			 counter=0;
			 }
				
			}
	
	}

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

void Timer3_Interrupt_Config(void)
{
	
	uwPrescalerValue = (uint32_t) ((SystemCoreClock /2) / 10000) - 1;
  
  /* Set TIM3 instance */
  Tim3Handle.Instance = TIM3;
   
  Tim3Handle.Init.Period = 10000 - 1;
  Tim3Handle.Init.Prescaler = uwPrescalerValue;        // timer interrupt every 1s
  Tim3Handle.Init.ClockDivision = 0;
  Tim3Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	
	if(HAL_TIM_Base_Init(&Tim3Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
	/*Start the TIM Base generation in interrupt mode */
  if(HAL_TIM_Base_Start_IT(&Tim3Handle) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
	
}

void Error_Handler(void)
{
  while(1) 
  {
  }
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{

}

#endif
	

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
