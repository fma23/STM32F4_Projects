#include "main.h"
#include <stdbool.h>


/* Global Variables*/
ADC_HandleTypeDef        Adc3Handle;
ADC_ChannelConfTypeDef   Adc3Config;

//volatile bool TransferComplete_Flag=false;

volatile uint32_t ADC3Data_Buffer[730]={0};

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void ADC3_Error_Handler(void)
{
  while(1)
  {
  }
}
/**
  * @brief  ADC3 Configuration
  * @param  None
  * @retval None
  */
void Configure_ADC3(void){
	
	/*1- Configure ADC3 peripheral */
  Adc3Handle.Instance          = ADC3;
 
  Adc3Handle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV8;
  Adc3Handle.Init.Resolution = ADC_RESOLUTION12b;
  Adc3Handle.Init.ScanConvMode = ENABLE;            
  Adc3Handle.Init.ContinuousConvMode = ENABLE;
  Adc3Handle.Init.DiscontinuousConvMode = DISABLE;
  Adc3Handle.Init.NbrOfDiscConversion = 0;
  Adc3Handle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  Adc3Handle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
  Adc3Handle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  Adc3Handle.Init.NbrOfConversion = 2;
  Adc3Handle.Init.DMAContinuousRequests = ENABLE;  
  Adc3Handle.Init.EOCSelection =DISABLE;

  HAL_ADC_Init(&Adc3Handle);
	
	if(HAL_ADC_Init(&Adc3Handle) != HAL_OK)
  {
    /* Initialization Error */
  ADC3_Error_Handler();
  }
  
  /*Configure ADC regular channel */  
  Adc3Config.Channel = ADC_CHANNEL_14;     
  Adc3Config.Rank = 1;
  Adc3Config.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  Adc3Config.Offset = 0;
  
  if(HAL_ADC_ConfigChannel(&Adc3Handle, &Adc3Config) != HAL_OK)
  {
    /* Channel Configuration Error */
   ADC3_Error_Handler();
  }
	
	  /*Configure ADC regular channel */  
  Adc3Config.Channel = ADC_CHANNEL_9; 
  Adc3Config.Rank = 2;
  Adc3Config.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  Adc3Config.Offset = 0;
  
  if(HAL_ADC_ConfigChannel(&Adc3Handle, &Adc3Config) != HAL_OK)
  {
    /* Channel Configuration Error */
   ADC3_Error_Handler();
  }
  
  /*##-3- Start the conversion process and enable interrupt ##################*/                                                                                                                                                                                                                          
  if(HAL_ADC_Start_DMA(&Adc3Handle, (uint32_t*)&ADC3Data_Buffer[0], 730) != HAL_OK)
  {
    /* Start Conversation Error */
   ADC3_Error_Handler(); 
  }
  
}

///**
//  * @brief  Conversion complete callback in non blocking mode 
//  * @param  AdcHandle : AdcHandle handle
//  * @note   This example shows a simple way to report end of conversion, and 
//  *         you can add your own implementation.    
//  * @retval None
//  */
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
//{
// TransferComplete_Flag=true; 
//}