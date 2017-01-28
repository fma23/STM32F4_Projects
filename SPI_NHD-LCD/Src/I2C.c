#include "main.h"


/* Variables Decalarations */
I2C_HandleTypeDef I2cHandle;
uint8_t I2C_DevSelectAddress_WR=0xA0;      //"10100000, WR bit =0; Chip Enable= 0; bit16=0;bit17=0
uint8_t I2C_DevSelectAddress_RD=0xA1;      //"10100001, WR bit =1; Chip Enable= 0; bit16=0;bit17=0
volatile uint16_t I2CMemAddress=0;        
uint8_t aRxBuffer =0;                      // write data to this variable;     


/* Functions Decalarations */
void Clear_I2C_RW(void); 
void Set_I2C_RW(void); 

/* ----------------------------------------------------------------------------------------------------*/







/**
  * I2C error handler
  */
void I2c_Error_Handler(void)
{
  while(1)
  {
  }
}

/* Configure the I2C peripheral */
/**
  * I2C Configuration
  */
void I2C_Config(void){

  I2cHandle.Instance             = I2C1;
  
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_10BIT;
  I2cHandle.Init.ClockSpeed      = 400000;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLED;
  I2cHandle.Init.OwnAddress1     = 0x0A;
  I2cHandle.Init.OwnAddress2     = 0xFE;
	
	  if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
  {
    /* Initialization Error */
    I2c_Error_Handler();    
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *Tim3Handle)
{
 static uint8_t Wrcount=0;
 uint8_t i, temp; 
	
	GPIOF->ODR ^= GPIO_ODR_ODR_10; 
	
	/*start writing to the EEPROM */
	Clear_I2C_RW();                 //RW set low: write enable

		if(Wrcount<10)
		{

			temp=HAL_I2C_Mem_Write(&I2cHandle, I2C_DevSelectAddress_WR, I2CMemAddress, 2, &Wrcount, 1,100);
			I2CMemAddress++;
			Wrcount++;

	   }
		else if(Wrcount==10)           //Start reading from the EEPROM
		{
			   I2CMemAddress=0;
				
		     Set_I2C_RW();             //RW set high: read enable 
			   
  			 EEPROM_Output();
			
	       data('\n');
			   data('\n');
			
				 for(i=0;i<10;i++)
			   {
				 HAL_I2C_Mem_Read(&I2cHandle,I2C_DevSelectAddress_RD, I2CMemAddress, 2, &aRxBuffer, 1, 100);
				 I2CMemAddress++;
         data((0x30)| (aRxBuffer));	
				 } 
				 Wrcount++;               //stop writing to the EEPROM
		}	
}
/**
  * Enable I2C write operation
  */
void Clear_I2C_RW()
{
GPIOA->ODR &= ~ GPIO_ODR_ODR_10; 
}
/**
  * Enable I2C READ operation
  */
void Set_I2C_RW(void)
{
GPIOA->ODR |= GPIO_ODR_ODR_10; 	
}