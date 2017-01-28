/**
  ******************************************************************************
  * Author: Farid Mabrouk
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
#include <stdbool.h>
#include <math.h>

TIM_HandleTypeDef Tim3Handle;
uint32_t uwPrescalerValue = 0;

extern volatile bool TransferComplete_Flag;
extern volatile uint32_t ADC3Data_Buffer[730];
volatile uint32_t PhaseA_RMSvalue=0; 
volatile uint32_t PhaseB_RMSvalue=0;

void SystemClock_Config(void);
void Error_Handler(void);



int main(void)
{

	uint16_t i=0;
	uint16_t j=1;
	signed int tempvalue1=0;
	signed int tempvalue2=0;
	 
	signed int tempvalue3=0;
	signed int tempvalue4=0;
	
	
  /*initialize the HAL Library */
  HAL_Init();

	/*System Clock Config */
  SystemClock_Config();
	
	/*GPIOs and LED Config */
	Configure_LEDs();

	/*GPIOs and ADC3 Config */
	Configure_ADC3();

	/*SPI Config */
	SPI2_Config();
	SPI_CS_RS_Config();
	
	/*NHD-0420CW-AB3 LCD Config */
	LCD_Init();	
	LCD_Output();
	
	/*TIMER3 Config */
	Timer3_Interrupt_Config();
	
  
	/*wait for interrupts*/
  while (1)
  {
		if(TransferComplete_Flag==true)
		{
			TransferComplete_Flag=false;
			
			  for(i=0;i<730;i+=2)
	      {
				tempvalue1=	ADC3Data_Buffer[i]-912;
		    tempvalue1=tempvalue1*tempvalue1;
		    tempvalue2=tempvalue2+tempvalue1;
	      
				tempvalue3=	ADC3Data_Buffer[j]-912;
		    tempvalue3=tempvalue3*tempvalue3;
		    tempvalue4=tempvalue4+tempvalue3;
				j=j+2;
				}
				
				PhaseA_RMSvalue= sqrt(tempvalue2); 
	      PhaseB_RMSvalue= sqrt(tempvalue4); 	
			
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
  Tim3Handle.Init.Prescaler = uwPrescalerValue;
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
